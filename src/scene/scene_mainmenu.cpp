#include <SDL3/SDL.h>
#include <numbers>
#include "scene/scene_mainmenu.h"
#include "engine/engine_input.h"
#include "manager/manager_scene.h"
#include "util/util_logger.h"

rgp::MainMenuScene::MainMenuScene(SceneManager& sceneManager, InputEngine& inputEngine, RendererEngine& renderer) : 
    Scene(sceneManager, inputEngine, renderer),
    m_sceneManager(sceneManager),
    m_initTime(Util::getElapsedGameTime())
{
	SDL_Log("Main menu scene loaded.");
}

rgp::MainMenuScene::~MainMenuScene() {
	SDL_Log("Main menu scene unloaded.");
}

void rgp::MainMenuScene::update() {
    m_now = Util::getElapsedGameTime() / 1000 - m_initTime;

    if (m_inputEngine.isKeyJustPressed(SDL_SCANCODE_P))
        m_sceneManager.changeScene(SceneManager::LEVEL_ONE);
}

void rgp::MainMenuScene::draw() {
    const auto red = static_cast<float>(0.5 + 0.5 * SDL_sin(m_now));
    const auto green = static_cast<float>(0.5 + 0.5 * SDL_sin(m_now + std::numbers::pi * 2 / 3));
    const auto blue = static_cast<float>(0.5 + 0.5 * SDL_sin(m_now + std::numbers::pi * 4 / 3));

    m_renderer.draw(red, green, blue, SDL_ALPHA_OPAQUE);
}