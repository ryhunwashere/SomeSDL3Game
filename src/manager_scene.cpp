#include <SDL3/SDL.h>
#include <memory>
#include <stdexcept>
#include <string>
#include <cassert>
#include "manager_scene.h"
#include "scene_mainmenu.h"
#include "scene_level1.h"

rgp::SceneManager::SceneManager(InputEngine& input, RendererEngine& renderer, TextureEngine& textureEngine) {
	m_sceneMap[MAIN_MENU] = [this, &input, &renderer]()					{ return std::make_unique<MainMenuScene>(*this, input, renderer); };
	m_sceneMap[LEVEL_ONE] = [this, &input, &renderer, &textureEngine]() { return std::make_unique<LevelOneScene>(*this, input, renderer, textureEngine); };

	changeScene(SceneEnum::LEVEL_ONE);

	SDL_Log("Scene manager loaded.");
}

rgp::SceneManager::~SceneManager() {
	SDL_Log("Scene manager unloaded.");
}

void rgp::SceneManager::changeScene(SceneEnum targetScene) {
	auto it = m_sceneMap.find(targetScene);

	assert(it != m_sceneMap.end());
	assert(it->second);

	m_currentScene = it->second();
}

void rgp::SceneManager::updateCurrentScene() {
	if (m_currentScene.get())
		m_currentScene.get()->update();
}

void rgp::SceneManager::drawCurrentScene() {
	if (m_currentScene.get())
		m_currentScene.get()->draw();
}
