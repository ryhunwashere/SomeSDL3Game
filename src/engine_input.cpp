#include <SDL3/SDL.h>
#include "engine_input.h"

void rgp::InputEngine::updateKeyState(SDL_Scancode scancode, bool isPressed) {
	m_keystateMap[scancode] = isPressed;
}

auto rgp::InputEngine::isKeyDown(SDL_Scancode scancode) const -> bool {
    auto iterator = m_keystateMap.find(scancode);

    if (iterator != m_keystateMap.end())
        return iterator->second;

    return false;
}