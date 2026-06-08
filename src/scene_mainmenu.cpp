#include <SDL3/SDL.h>
#include <charconv>
#include <cmath>
#include <numbers>
#include "scene_mainmenu.h"
#include "engine_renderer.h"
#include "engine_input.h"
#include "manager_scene.h"
#include "util_logger.h"

rgp::MainMenuScene::MainMenuScene() : m_initTime(rgp::Util::getElapsedGameTime()) {
	SDL_Log("Main menu scene loaded.");
}

rgp::MainMenuScene::~MainMenuScene() {
	SDL_Log("Main menu scene unloaded.");
}

void rgp::MainMenuScene::update() {
    m_now = rgp::Util::getElapsedGameTime() / 1000 - m_initTime;

    if (rgp::InputEngine::get().isKeyJustPressed(SDL_SCANCODE_P))
        rgp::SceneManager::get().changeScene(SceneManager::LEVEL_ONE);
}

void rgp::MainMenuScene::draw() {
    const auto red = static_cast<float>(0.5 + 0.5 * SDL_sin(m_now));
    const auto green = static_cast<float>(0.5 + 0.5 * SDL_sin(m_now + std::numbers::pi * 2 / 3));
    const auto blue = static_cast<float>(0.5 + 0.5 * SDL_sin(m_now + std::numbers::pi * 4 / 3));

    rgp::RendererEngine::get().draw(red, green, blue, SDL_ALPHA_OPAQUE);
}