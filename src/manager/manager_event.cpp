#include "manager/manager_event.h"

rgp::EventManager::EventManager() : m_eventNum(SDL_RegisterEvents(1)) {
    if (m_eventNum == 0)
        throw SDLException("Register event error");

    SDL_SetEventEnabled(m_eventNum, true);
}

rgp::EventManager::~EventManager() {
    SDL_FlushEvent(m_eventNum);
    SDL_SetEventEnabled(m_eventNum, false);
}

auto rgp::EventManager::processEvent(const SDL_Event& event) -> bool {
    if (event.type != m_eventNum) return false;

    if (const std::unique_ptr<EventVariant> safeEvent(static_cast<EventVariant*>(event.user.data1)); safeEvent)
        dispatch(*safeEvent);

    return true;
}

void rgp::EventManager::dispatch(const EventVariant& eventVariant) {
    std::visit([this, &eventVariant]([[maybe_unused]] auto&& concreteEvent) {
        if (const auto typeId = std::type_index(typeid(concreteEvent)); m_Listeners.contains(typeId)) {
            for (auto& callbackFn : m_Listeners[typeId])
                callbackFn(eventVariant);
        }
    }, eventVariant);
}