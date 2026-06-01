#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "entity_text.h"

class Game {
public:
    Game() = default;
    ~Game() = default;

    bool initialize();
    void handle_event(SDL_Event* event);
    void update();
    void render();
    void shutdown();

private:
    TTF_Font* m_mainFont = nullptr;
    float m_fontSize = 24.0f;

    entity::TextEntity m_timer_text;
    entity::TextEntity m_fps_text;

    float m_text_pos_x = 100.0f;
    float m_text_pos_y = 100.0f;
    char m_text_buffer[64]{};
};