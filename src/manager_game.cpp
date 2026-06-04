#include <charconv>
#include <cmath>
#include <stdexcept>
#include <memory>
#include "manager_game.h"
#include "engine_renderer.h"
#include "engine_input.h"
#include "manager_font.h"

using namespace manager;

constexpr float MOVE_SPEED = 4.0f;

GameManager::GameManager() {
    if (!SDL_InitSubSystem(SDL_INIT_VIDEO)) 
        throw std::runtime_error(
            std::string("SDL video initialization failure: ") + SDL_GetError()
        );

    m_timerText = std::make_unique<entity::TextEntity>("ZenMaruGothic-Medium.ttf", "");
    m_timerText->setColor(0.0, 0.0, 0.0);

    SDL_Log("GameManager and subsystems initialized.");
}

GameManager::~GameManager() {
    SDL_Quit();
    SDL_Log("GameManager and subsystems unloaded.");
}

GameManager& GameManager::get() {
    static GameManager instance;
    return instance;
}

void GameManager::handleEvent(SDL_Event* event) {
    engine::InputEngine& input = engine::InputEngine::get();

    if (event->type == SDL_EVENT_KEY_DOWN) 
        input.updateKeyState(event->key.key, true);
    else if (event->type == SDL_EVENT_KEY_UP) 
        input.updateKeyState(event->key.key, false);
}

void GameManager::update() {
    const double now = static_cast<double>(SDL_GetTicks()) / 1000.0;
    const double rounded_now = std::round(now * 10.0) / 10.0;

    auto [ptr, ec] = std::to_chars(m_textBuffer, m_textBuffer + sizeof(m_textBuffer), rounded_now, std::chars_format::fixed, 1);
    if (ec == std::errc()) {
        std::string timeStr(m_textBuffer, ptr - m_textBuffer);
        m_timerText->updateText(timeStr);
    }

    engine::InputEngine& input = engine::InputEngine::get();

    if (input.isKeyDown(SDLK_W))
        m_timerText->move(0.0f, -m_timerTextSpeed);
    if (input.isKeyDown(SDLK_S))
        m_timerText->move(0.0f, m_timerTextSpeed);
    if (input.isKeyDown(SDLK_A))
        m_timerText->move(-m_timerTextSpeed, 0.0f);
    if (input.isKeyDown(SDLK_D))
        m_timerText->move(m_timerTextSpeed, 0.0f);
}

void GameManager::draw() {
    const double now = static_cast<double>(SDL_GetTicks()) / 1000.0;
    const float red = static_cast<float>(0.5 + 0.5 * SDL_sin(now));
    const float green = static_cast<float>(0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 2 / 3));
    const float blue = static_cast<float>(0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 4 / 3));

    engine::RendererEngine& renderer = engine::RendererEngine::get();

    renderer.clear(red, green, blue);

    m_timerText->draw();

    renderer.present();
}
