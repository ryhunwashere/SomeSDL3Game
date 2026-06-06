#pragma once
#include <unordered_map>
#include <SDL3/SDL.h>
#include "abstract_singleton.h"

namespace rgp {
    class InputEngine : public Singleton<InputEngine> {
        friend class Singleton<InputEngine>;

    public:
        void updateKeyState(SDL_Scancode scancode, bool isPressed);
        [[nodiscard]] auto isKeyDown(SDL_Scancode scancode) const -> bool;

    private:
        InputEngine()   = default;
        ~InputEngine()  = default;

        std::unordered_map<SDL_Scancode, bool> m_keystateMap;
    };
};