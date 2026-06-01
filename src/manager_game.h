#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "entity_text.h"

namespace manager {
    class GameManager {
    public:
        GameManager() = default;
        ~GameManager() = default;

        bool initialize();
        void handle_event(SDL_Event* event);
        void update();
        void draw();
        void shutdown();

    private:
        TTF_Font* m_main_font = nullptr;
        entity::TextEntity m_timer_text;
        float m_font_size = 100.0f;
        char m_text_buffer[256]{};
    };
};