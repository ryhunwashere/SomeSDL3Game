#include "manager/manager_event.h"

rgp::EventManager::EventManager() : m_eventNum(SDL_RegisterEvents(1)) {
    if (m_eventNum == 0) throw SDLException("Register event error");
    SDL_SetEventEnabled(m_eventNum, true);
}

rgp::EventManager::~EventManager() {
    SDL_FlushEvent(m_eventNum);
    SDL_SetEventEnabled(m_eventNum, false);
}

auto rgp::EventManager::processEvent(const SDL_Event& event) -> bool {
    if (event.type != m_eventNum) return false;

    if (auto* variantPtr = static_cast<EventVariant*>(event.user.data1)) [[likely]] {
        dispatch(*variantPtr);
        *variantPtr = std::monostate{};
    }

    return true;
}

void rgp::EventManager::dispatch(const EventVariant& eventVariant) {
    if (std::holds_alternative<std::monostate>(eventVariant)) return;

    std::visit([this]<typename T>(const T& concreteEvent) -> void {
        if constexpr (std::is_same_v<std::decay_t<T>, std::monostate>) return;

        const auto typeId = std::type_index(typeid(concreteEvent));
        const auto it = m_listeners.find(typeId);

        if (it == m_listeners.end()) return;

        for (const auto& callbackFn : it->second)
            callbackFn(static_cast<const void*>(&concreteEvent));
    }, eventVariant);
}