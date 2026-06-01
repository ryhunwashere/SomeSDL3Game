#include "game.h"
#include "engine_renderer.h"
#include "engine_input.h"
#include "manager_text.h"
#include <charconv>
#include <cmath>

using namespace engine;
using namespace manager;
using namespace engine;

constexpr float MOVE_SPEED = 4.0f;

bool Game::initialize() {
    if (!SDL_InitSubSystem(SDL_INIT_VIDEO)) return false;
    if (!RendererEngine::get().initialize("Multi-Text Window", 640, 480)) return false;

    if (!TextManager::get().initialize(RendererEngine::get().get_sdl_renderer())) return false;

    m_mainFont = TextManager::get().load_font("ZenMaruGothic-Medium.ttf", m_fontSize);
    if (!m_mainFont) return false;

    if (!m_timer_text.create(m_mainFont, "")) return false;
    m_timer_text.set_color_float(0.0, 0.0, 0.0); // Black color

    if (!m_fps_text.create(m_mainFont, "will be an fps counter here later")) return false;
    m_fps_text.set_color_float(255.0, 255.0, 255.0); // White color

    return true;
}

void Game::handle_event(SDL_Event* event) 
{
    if (event->type == SDL_EVENT_KEY_DOWN) 
    {
        InputEngine::get().update_key(event->key.key, true);

        if (event->key.key == SDLK_P && m_mainFont) 
        {
            m_fontSize += 1.0f;
            TTF_SetFontSize(m_mainFont, m_fontSize);
        }

        if (event->key.key == SDLK_O && m_mainFont) 
        {
            m_fontSize = SDL_max(1.0f, m_fontSize - 1.0f);
            TTF_SetFontSize(m_mainFont, m_fontSize);
        }
    }
    else if (event->type == SDL_EVENT_KEY_UP) 
    {
        InputEngine::get().update_key(event->key.key, false);
    }
}

void Game::update() {
    const InputEngine input = InputEngine::get();

    if (input.is_key_down(SDLK_W)) m_text_pos_y -= MOVE_SPEED;
    if (input.is_key_down(SDLK_S)) m_text_pos_y += MOVE_SPEED;
    if (input.is_key_down(SDLK_A)) m_text_pos_x -= MOVE_SPEED;
    if (input.is_key_down(SDLK_D)) m_text_pos_x += MOVE_SPEED;

    const double now = static_cast<double>(SDL_GetTicks()) / 1000.0;
    const double rounded_now = std::round(now * 10.0) / 10.0;

    auto [ptr, ec] = std::to_chars(m_text_buffer, m_text_buffer + sizeof(m_text_buffer), rounded_now, std::chars_format::fixed, 1);
    if (ec == std::errc()) 
    {
        std::string timeStr(m_text_buffer, ptr - m_text_buffer);
        m_timer_text.update_text(timeStr); // Updates only the timer text
    }
}

void Game::render()
{
    const double now = static_cast<double>(SDL_GetTicks()) / 1000.0;
    const float red = static_cast<float>(0.5 + 0.5 * SDL_sin(now));
    const float green = static_cast<float>(0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 2 / 3));
    const float blue = static_cast<float>(0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 4 / 3));

    RendererEngine::get().clear(red, green, blue);

    m_timer_text.draw(m_text_pos_x, m_text_pos_y);
    m_fps_text.draw(20.0f, 20.0f);

    RendererEngine::get().present();
}

void Game::shutdown() 
{
    // Clean up individual text objects
    m_timer_text.destroy();
    m_fps_text.destroy();

    if (m_mainFont) TTF_CloseFont(m_mainFont);

    TextManager::get().shutdown();
    RendererEngine::get().shutdown();
    SDL_Quit();
}