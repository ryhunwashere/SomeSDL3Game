#pragma once

#include <cassert>
#include <functional>
#include <typeindex>
#include <variant>
#include <unordered_map>
#include <vector>
#include <concepts>
#include <mutex>
#include <SDL3/SDL_events.h>

#include "event/event.h"
#include "event/event_scene_change.h"
#include "event/event_player_lives_change.h"
#include "event/event_pause_state_change.h"

#include "except_sdl.h"

namespace rgp {
    class EventManager {
    public:
        EventManager();
        ~EventManager();

        EventManager(const EventManager&)            = delete;
        EventManager& operator=(const EventManager&) = delete;

        template <std::derived_from<event::Event> TEvent>
        void publish(TEvent&& concreteEvent) {
            auto lock = std::lock_guard(m_poolMutex);

            size_t safetyCounter = 0;
            while (!std::holds_alternative<std::monostate>(m_eventPool[m_poolIndex])) {
                m_poolIndex = (m_poolIndex + 1) % MAX_EVENTS;
                ++safetyCounter;
                assert(safetyCounter <= MAX_EVENTS && "Event pool exhausted.");
            }

            m_eventPool[m_poolIndex] = std::forward<TEvent>(concreteEvent);

            SDL_Event event;
            SDL_zero(event);
            event.type = m_eventNum;
            event.user.data1 = &m_eventPool[m_poolIndex];

            if (!SDL_PushEvent(&event)) [[unlikely]] {
                m_eventPool[m_poolIndex] = std::monostate{}; // Rollback slot on failure
                throw SDLException("Failed to push event.");
            }

            m_poolIndex = (m_poolIndex + 1) % MAX_EVENTS;
        }

        template <std::derived_from<event::Event> TEvent>
        void publishSync(const TEvent& concreteEvent) {
            const auto typeId = std::type_index(typeid(concreteEvent));
            const auto it = m_listeners.find(typeId);

            if (it == m_listeners.end()) return;

            for (const auto& callbackFn : it->second)
                callbackFn(static_cast<const void*>(&concreteEvent));
        }

        template <std::derived_from<event::Event> TEvent>
        void subscribe(std::invocable<const TEvent&> auto&& callbackFn) {
            m_listeners[std::type_index(typeid(TEvent))].push_back(
                [callbackFn = std::forward<decltype(callbackFn)>(callbackFn)](const void* eventPtr) -> void {
                    std::invoke(callbackFn, *static_cast<const TEvent*>(eventPtr));
                }
            );
        }

        auto processEvent(const SDL_Event& event) -> bool;

    private:
        static constexpr size_t MAX_EVENTS = 512;
        using EventVariant = std::variant<
            std::monostate,
            event::SceneChangeEvent,
            event::PlayerLivesChangeEvent,
            event::PauseStateChangeEvent
        >;
        using EventCallbackFn = std::function<void(const void*)>;

        void dispatch(const EventVariant& eventVariant);

        const uint32_t m_eventNum;
        std::unordered_map<std::type_index, std::vector<EventCallbackFn>> m_listeners;

        std::array<EventVariant, MAX_EVENTS> m_eventPool{};
        size_t m_poolIndex = 0;
        std::mutex m_poolMutex;
    };
}
