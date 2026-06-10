#include <SDL3/SDL.h>
#include <memory>
#include <string>
#include <cassert>
#include "manager_scene.h"
#include "scene_mainmenu.h"
#include "scene_level1.h"

rgp::SceneManager::SceneManager(InputEngine& inputEngine, RendererEngine& renderer, TextureEngine& textureEngine) {
	m_sceneMap[MAIN_MENU] = [this, &inputEngine, &renderer] {
		return std::make_unique<MainMenuScene>(*this, inputEngine, renderer);
	};

	m_sceneMap[LEVEL_ONE] = [this, &inputEngine, &renderer, &textureEngine] {
		return std::make_unique<LevelOneScene>(*this, inputEngine, renderer, textureEngine);
	};

	changeScene(LEVEL_ONE);

	SDL_Log("Scene manager loaded.");
}

rgp::SceneManager::~SceneManager() {
	SDL_Log("Scene manager unloaded.");
}

void rgp::SceneManager::changeScene(const SceneEnum targetScene) {
	const auto it = m_sceneMap.find(targetScene);

	assert(it != m_sceneMap.end());
	assert(it->second);

	m_currentScene = it->second();
}

void rgp::SceneManager::updateCurrentScene() const {
	if (m_currentScene)
		m_currentScene->update();
}

void rgp::SceneManager::drawCurrentScene() const {
	if (m_currentScene)
		m_currentScene->draw();
}
