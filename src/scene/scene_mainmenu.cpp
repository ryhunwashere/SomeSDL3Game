#include <SDL3/SDL.h>
#include "scene/scene_mainmenu.h"
#include "manager/manager_scene.h"
#include "util/util_logger.h"

rgp::MainMenuScene::MainMenuScene(GameContext& ctx) : Scene(ctx),
    m_initTime(static_cast<float>(Util::getElapsedGameTime()))
{
	SDL_Log("Main menu scene loaded.");
}

rgp::MainMenuScene::~MainMenuScene() {
	SDL_Log("Main menu scene unloaded.");
}

auto rgp::MainMenuScene::update() -> SceneType {
    m_now = static_cast<float>(Util::getElapsedGameTime()) / 1000 - m_initTime;

    if (m_ctx.getInputEngine().isKeyJustPressed(SDL_SCANCODE_P))
        return SceneType::LevelOne;

    return SceneType::Continue;
}

void rgp::MainMenuScene::draw() {
    const auto red = 0.5f + 0.5f * SDL_sinf(m_now);
    const auto green = 0.5f + 0.5f * SDL_sinf(m_now + SDL_PI_F * 2 / 3);
    const auto blue = 0.5f + 0.5f * SDL_sinf(m_now + SDL_PI_F * 4 / 3);

    m_ctx.getRendererEngine().draw(red, green, blue, SDL_ALPHA_OPAQUE);
}