#pragma once
#include <SDL3/SDL.h>
#include <unordered_map>
#include "abstract_singleton.h"

namespace engine {
    class InputEngine : public abstract::Singleton<InputEngine> {
        friend class abstract::Singleton<InputEngine>;

    public:
        void updateKeyState(SDL_Keycode key, bool isPressed);
        [[nodiscard]] auto isKeyDown(SDL_Keycode key) const -> bool;

    private:
        InputEngine()   = default;
        ~InputEngine()  = default;

        std::unordered_map<SDL_Keycode, bool> m_keystateMap;
    };
};