#include <SDL3/SDL.h>
#include "manager/manager_input.h"

void rgp::InputManager::keepTrackOfPreviousState() {
    m_previousKeys = m_currentKeys;
}

void rgp::InputManager::updateKeyDownState(const SDL_Scancode scancode, const bool isDown) {
    m_currentKeys[scancode] = isDown;
}

auto rgp::InputManager::isKeyDown(const SDL_Scancode scancode) const -> bool {
    const auto it = m_currentKeys.find(scancode);
    return it != m_currentKeys.end() ? it->second : false;
}

auto rgp::InputManager::isKeyJustPressed(const SDL_Scancode scancode) const -> bool {
    const auto itCurrent = m_currentKeys.find(scancode);
    const bool currentDown = itCurrent != m_currentKeys.end() ? itCurrent->second : false;

    const auto itPrevious = m_previousKeys.find(scancode);
    const bool previousDown = itPrevious != m_previousKeys.end() ? itPrevious->second : false;

    // true if down now, but wasn't down in the last frame
    return currentDown && !previousDown;
}