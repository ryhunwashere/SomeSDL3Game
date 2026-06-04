#pragma once
#include <SDL3/SDL.h>
#include <unordered_map>

namespace engine {
    class InputEngine {
    public:
        static auto get() -> InputEngine& {
            static InputEngine instance;
            return instance;
        }

        void updateKeyState(SDL_Keycode key, bool isPressed);

        [[nodiscard]] auto isKeyDown(SDL_Keycode key) const -> bool;

        // Prevent copying and moving
        InputEngine(const InputEngine&)                     = delete;
        auto operator=(const InputEngine&) -> InputEngine&  = delete;
        InputEngine(InputEngine&&)                          = delete;
        auto operator=(InputEngine&&) -> InputEngine&       = delete;

    private:
        InputEngine()   = default;
        ~InputEngine()  = default;
        std::unordered_map<SDL_Keycode, bool> m_keystateMap;
    };
};