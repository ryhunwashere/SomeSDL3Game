#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <charconv>
#include <stdexcept>
#include "manager_game.h"
#include "engine_renderer.h"
#include "engine_input.h"

//constexpr float MOVE_SPEED = 4.0f;

rgp::GameManager::GameManager() {
    if (!SDL_InitSubSystem(SDL_INIT_VIDEO)) 
        throw std::runtime_error(
            std::string("SDL video initialization failure: ") + SDL_GetError()
        );

    m_timerText = std::make_unique<rgp::TextEntity>("ZenMaruGothic-Medium.ttf");
    m_timerText->setColor({ 255, 255, 255, SDL_ALPHA_OPAQUE });

    m_player = std::make_unique<rgp::PlayerEntity>("player1_sprite.png");

    SDL_Log("GameManager and subsystems initialized.");
}

rgp::GameManager::~GameManager() {
    SDL_Quit();
    SDL_Log("GameManager and subsystems unloaded.");
}

void rgp::GameManager::handleEvent(SDL_Event* event) {
    auto& input = rgp::InputEngine::get();

    if (event->type == SDL_EVENT_KEY_DOWN) 
        input.updateKeyState(event->key.scancode, true);
    else if (event->type == SDL_EVENT_KEY_UP) 
        input.updateKeyState(event->key.scancode, false);
}

void rgp::GameManager::update() {
    const double now = static_cast<double>(SDL_GetTicks()) / 1000.0;
    const double roundedNow = std::round(now * 10.0) / 10.0;

    auto [ptr, ec] = std::to_chars(
        m_textBuffer.data(), 
        m_textBuffer.data() + m_textBuffer.size(), 
        roundedNow, 
        std::chars_format::fixed, 
        1
    );

    if (ec == std::errc()) {
        std::string timeStr(m_textBuffer.data(), ptr - m_textBuffer.data());
        m_timerText->setText(timeStr);
    }

    m_player->update();

    //auto& input = rgp::InputEngine::get();

    //if (input.isKeyDown(SDL_SCANCODE_W)) m_timerText->moveY(-MOVE_SPEED);
    //if (input.isKeyDown(SDL_SCANCODE_S)) m_timerText->moveY(MOVE_SPEED);
    //if (input.isKeyDown(SDL_SCANCODE_A)) m_timerText->moveX(-MOVE_SPEED);
    //if (input.isKeyDown(SDL_SCANCODE_D)) m_timerText->moveX(MOVE_SPEED);
}

void rgp::GameManager::draw() {
    //const double now    = static_cast<double>(SDL_GetTicks()) / 1000.0;
    //const auto red      = static_cast<float>(0.5 + 0.5 * SDL_sin(now));
    //const auto green    = static_cast<float>(0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 2 / 3));
    //const auto blue     = static_cast<float>(0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 4 / 3));

    auto& renderer = rgp::RendererEngine::get();

    renderer.clear();

    //renderer.draw(red, green, blue, SDL_ALPHA_OPAQUE);
    m_player->draw();
    m_timerText->draw();

    renderer.present();
}
