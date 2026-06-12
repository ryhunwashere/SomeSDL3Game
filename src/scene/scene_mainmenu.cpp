#include <SDL3/SDL.h>
#include <numbers>
#include "scene/scene_mainmenu.h"
#include "engine/engine_input.h"
#include "engine/engine_renderer.h"
#include "manager/manager_scene.h"
#include "util/util_logger.h"

rgp::MainMenuScene::MainMenuScene(GameContext& ctx) : Scene(ctx), m_initTime(Util::getElapsedGameTime()) {
	SDL_Log("Main menu scene loaded.");
}

rgp::MainMenuScene::~MainMenuScene() {
	SDL_Log("Main menu scene unloaded.");
}

auto rgp::MainMenuScene::update() -> SceneType {
    m_now = Util::getElapsedGameTime() / 1000 - m_initTime;

    if (m_ctx.inputEngine.isKeyJustPressed(SDL_SCANCODE_P))
        return SceneType::LevelOne;

    return SceneType::Continue;
}

void rgp::MainMenuScene::draw() {
    const auto red = 0.5 + 0.5 * SDL_sin(m_now);
    const auto green = 0.5 + 0.5 * SDL_sin(m_now + std::numbers::pi * 2 / 3);
    const auto blue = 0.5 + 0.5 * SDL_sin(m_now + std::numbers::pi * 4 / 3);

    m_ctx.renderer.draw(red, green, blue, SDL_ALPHA_OPAQUE);
}