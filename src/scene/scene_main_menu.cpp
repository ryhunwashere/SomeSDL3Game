#include <SDL3/SDL.h>
#include "scene/scene_main_menu.h"
#include "manager/manager_scene.h"

rgp::MainMenuScene::MainMenuScene(GameContext& ctx) : Scene(ctx), m_menuMusic(std::make_unique<TrackEntity>(m_ctx.getAudioManager(), AudioType::MenuMusic, true)) {
    m_menuMusic->play();
	SDL_Log("Main menu scene loaded.");
}

rgp::MainMenuScene::~MainMenuScene() {
	SDL_Log("Main menu scene unloaded.");
}

auto rgp::MainMenuScene::update() -> SceneType {
    m_now += m_ctx.getTimeManager().getDeltaTime();

    const auto& input = m_ctx.getInputManager();

    if (input.isKeyJustPressed(SDL_SCANCODE_P))
        return SceneType::LevelOne;

    if (input.isKeyJustPressed(SDL_SCANCODE_BACKSPACE)) {
        if (m_menuMusic->isPaused())
            m_menuMusic->resume();
        else if (m_menuMusic->isPlaying())
            m_menuMusic->pause();
    }

    return SceneType::Continue;
}

void rgp::MainMenuScene::draw() {
    const auto interval = m_now * 2.0f;
    const auto red      = 0.5f + 0.5f * SDL_sinf(interval);
    const auto green    = 0.5f + 0.5f * SDL_sinf(interval + SDL_PI_F * 2.0f / 3.0f);
    const auto blue     = 0.5f + 0.5f * SDL_sinf(interval + SDL_PI_F * 4.0f / 3.0f);

    m_ctx.getRendererEngine().draw(red, green, blue, SDL_ALPHA_OPAQUE_FLOAT);
}