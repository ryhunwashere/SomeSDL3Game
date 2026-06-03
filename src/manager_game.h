#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "entity_text.h"

namespace manager {
    class GameManager {
    public:
        GameManager() = default;
        ~GameManager() = default;

        bool init();
        void handleEvent(SDL_Event * event);
        void update();
        void draw();
        void shutdown();

    private:
        entity::TextEntity m_timerText;
        float m_timerTextSpeed = 5.0f;
        char m_textBuffer[256]{};
    };
};