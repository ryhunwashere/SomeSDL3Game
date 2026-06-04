#pragma once
#include <SDL3/SDL.h>
#include <unordered_map>

namespace engine {
    class InputEngine {
    public:
        static InputEngine& get() {
            static InputEngine s_instance;
            return s_instance;
        }

        void updateKeyState(SDL_Keycode key, bool isPressed);

        bool isKeyDown(SDL_Keycode key) const;

        // Prevent copying and moving
        InputEngine(const InputEngine&)             = delete;
        InputEngine& operator=(const InputEngine&)  = delete;
        InputEngine(InputEngine&&)                  = delete;
        InputEngine& operator=(InputEngine&&)       = delete;

    private:
        InputEngine()   = default;
        ~InputEngine()  = default;
        std::unordered_map<SDL_Keycode, bool> m_keystateMap;
    };
};