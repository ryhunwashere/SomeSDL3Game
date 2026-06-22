#pragma once

#include <functional>
#include <typeindex>
#include <variant>
#include <unordered_map>
#include <vector>
#include <memory>
#include <concepts>
#include <SDL3/SDL_events.h>

#include "event/event.h"
#include "event/event_scene_change.h"
#include "except_sdl.h"


namespace rgp {
    class EventManager {
    public:
        EventManager();
        ~EventManager();

        template <std::derived_from<event::Event> TEvent>
        void publish(TEvent&& concreteEvent) {
            SDL_Event event;
            SDL_zero(event);
            event.type = m_eventNum;

            auto eventData = std::make_unique<EventVariant>(std::forward<TEvent>(concreteEvent));
            event.user.data1 = static_cast<void*>(eventData.release());

            if (!SDL_PushEvent(&event))
                throw SDLException("Failed to push event.");
        }

        template <std::derived_from<event::Event> TEvent>
        void subscribe(std::invocable<const TEvent&> auto&& callbackFn) {
            m_Listeners[std::type_index(typeid(TEvent))].push_back(
                [callbackFn = std::forward<decltype(callbackFn)>(callbackFn)](const EventVariant& eventVariant) {
                    if (const auto* concreteEvent = std::get_if<TEvent>(&eventVariant))
                        std::invoke(callbackFn, *concreteEvent);
                }
            );
        }

        auto processEvent(const SDL_Event& event) -> bool;

    private:
        using EventVariant      = std::variant<event::SceneChangeEvent>;
        using EventCallbackFn   = std::function<void(const EventVariant&)>;

        void dispatch(const EventVariant& eventVariant);

        const uint32_t m_eventNum;
        std::unordered_map<std::type_index, std::vector<EventCallbackFn>> m_Listeners;
    };
}
