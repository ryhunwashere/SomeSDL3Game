#include "manager_game.h"
#include "engine_renderer.h"
#include "engine_input.h"
#include "manager_text.h"
#include <charconv>
#include <cmath>

constexpr float MOVE_SPEED = 4.0f;

bool manager::GameManager::initialize() 
{
    if (!SDL_InitSubSystem(SDL_INIT_VIDEO)) return false;

    if (!engine::RendererEngine::get().initialize("This is a window", 640, 480)) return false;

    if (!manager::TextManager::get().initialize(engine::RendererEngine::get().get_sdl_renderer())) return false;

    m_main_font = manager::TextManager::get().load_font("ZenMaruGothic-Medium.ttf", "zenmaru", m_font_size);

    if (!m_main_font) return false;

    if (!m_timer_text.create(m_main_font, "")) return false;
    m_timer_text.set_color_float(0.0, 0.0, 0.0);

    return true;
}

void manager::GameManager::handle_event(SDL_Event* event)
{
    engine::InputEngine& input = engine::InputEngine::get();

    if (event->type == SDL_EVENT_KEY_DOWN) 
        input.update_key_state(event->key.key, true);
    else if (event->type == SDL_EVENT_KEY_UP) 
        input.update_key_state(event->key.key, false);
}

void manager::GameManager::update() 
{
    const double now = static_cast<double>(SDL_GetTicks()) / 1000.0;
    const double rounded_now = std::round(now * 10.0) / 10.0;

    auto [ptr, ec] = std::to_chars(m_text_buffer, m_text_buffer + sizeof(m_text_buffer), rounded_now, std::chars_format::fixed, 1);
    if (ec == std::errc()) 
    {
        std::string timeStr(m_text_buffer, ptr - m_text_buffer);
        m_timer_text.update_text(timeStr);
    }

    const engine::InputEngine& input = engine::InputEngine::get();

    if (input.is_key_down(SDLK_W))
        m_timer_text.move(0.0f, -10.0f);
    if (input.is_key_down(SDLK_S))
        m_timer_text.move(0.0f, 10.0f);
    if (input.is_key_down(SDLK_A))
        m_timer_text.move(-10.0f, 0.0f);
    if (input.is_key_down(SDLK_D))
        m_timer_text.move(10.0f, 0.0f);

    if (input.is_key_down(SDLK_P) && m_main_font)
    {
        m_font_size += 1.0f;
        TTF_SetFontSize(m_main_font, m_font_size);
    }

    if (input.is_key_down(SDLK_O) && m_main_font)
    {
        m_font_size = SDL_max(1.0f, m_font_size - 1.0f);
        TTF_SetFontSize(m_main_font, m_font_size);
    }
}

void manager::GameManager::draw()
{
    const double now = static_cast<double>(SDL_GetTicks()) / 1000.0;
    const float red = static_cast<float>(0.5 + 0.5 * SDL_sin(now));
    const float green = static_cast<float>(0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 2 / 3));
    const float blue = static_cast<float>(0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 4 / 3));

    engine::RendererEngine& renderer = engine::RendererEngine::get();

    renderer.clear(red, green, blue);

    m_timer_text.draw();

    renderer.present();
}

void manager::GameManager::shutdown() 
{
    m_timer_text.destroy();

    if (m_main_font) TTF_CloseFont(m_main_font);

    manager::TextManager::get().shutdown();
    engine::RendererEngine::get().shutdown();

    SDL_Quit();
}