#include <SDL3/SDL.h>
#include <charconv>
#include <cmath>
#include <numbers>
#include "scene_mainmenu.h"
#include "engine_renderer.h"
#include "engine_input.h"
#include "manager_scene.h"
#include "util_logger.h"

rgp::MainMenuScene::MainMenuScene() : 
    m_initTime(rgp::Util::getElapsedGameTime()), 
    m_timerText(std::make_unique<rgp::TextEntity>("ZenMaruGothic-Medium.ttf")) 
{
	m_timerText->setColor({ 255, 255, 255, SDL_ALPHA_OPAQUE });

	SDL_Log("\nMain menu scene loaded.");
}

rgp::MainMenuScene::~MainMenuScene() {
	SDL_Log("\nMain menu scene unloaded.");
}

void rgp::MainMenuScene::update() {
    m_now = rgp::Util::getElapsedGameTime() - m_initTime;
    const double roundedNow = std::round(m_now * 10.0) / 10.0;

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

    if (rgp::InputEngine::get().isKeyJustPressed(SDL_SCANCODE_P))
        rgp::SceneManager::get().changeScene(SceneManager::LEVEL_ONE);
}

void rgp::MainMenuScene::draw() {
    const auto red = static_cast<float>(0.5 + 0.5 * SDL_sin(m_now));
    const auto green = static_cast<float>(0.5 + 0.5 * SDL_sin(m_now + std::numbers::pi * 2 / 3));
    const auto blue = static_cast<float>(0.5 + 0.5 * SDL_sin(m_now + std::numbers::pi * 4 / 3));

    rgp::RendererEngine::get().draw(red, green, blue, SDL_ALPHA_OPAQUE);

    m_timerText->draw();
}