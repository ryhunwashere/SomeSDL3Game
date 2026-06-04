#include "engine_input.h"

using namespace engine;

void InputEngine::updateKeyState(SDL_Keycode key, bool isPressed) {
	m_keystateMap[key] = isPressed;
}

auto InputEngine::isKeyDown(SDL_Keycode key) const -> bool {
	auto iterator = m_keystateMap.find(key);
	return iterator != m_keystateMap.end() ? iterator->second : false;
}