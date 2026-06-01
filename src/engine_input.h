#pragma once
#include <SDL3/SDL.h>
#include <unordered_map>

namespace engine {
    class InputEngine {
    public:
        static InputEngine& get()
        {
            static InputEngine s_instance;
            return s_instance;
        }

        void update_key(SDL_Keycode key, bool is_pressed)
        {
            m_keystates_map[key] = is_pressed;
        }

        bool is_key_down(SDL_Keycode key) const
        {
            auto it = m_keystates_map.find(key);
            return it != m_keystates_map.end() ? it->second : false;
        }

    private:
        InputEngine() = default;
        std::unordered_map<SDL_Keycode, bool> m_keystates_map;
    };
};