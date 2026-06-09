#pragma once
#include <unordered_map>
#include <SDL3/SDL_scancode.h>

namespace rgp {
    class InputEngine {
    public:
        InputEngine() = default;
        ~InputEngine() = default;

        void keepTrackOfPreviousState();
        void updateKeyDownState(SDL_Scancode scancode, bool isDown);

        [[nodiscard]] auto isKeyDown(SDL_Scancode scancode) const -> bool;
        [[nodiscard]] auto isKeyJustPressed(SDL_Scancode scancode) const -> bool;

    private:
        std::unordered_map<SDL_Scancode, bool> m_currentKeys;
        std::unordered_map<SDL_Scancode, bool> m_previousKeys;
    };
};