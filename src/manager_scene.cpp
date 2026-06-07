#include <SDL3/SDL.h>
#include <memory>
#include <stdexcept>
#include <string>
#include "manager_scene.h"
#include "scene_mainmenu.h"
#include "scene_level1.h"

rgp::SceneManager::SceneManager() {
	m_sceneMap[MAIN_MENU] = []() { return std::make_unique<MainMenuScene>(); };
	m_sceneMap[LEVEL_ONE] = []() { return std::make_unique<LevelOneScene>(); };

	m_currentScene = std::make_unique<MainMenuScene>();

	SDL_Log("Scene manager loaded.");
}

rgp::SceneManager::~SceneManager() {
	SDL_Log("Scene manager unloaded.");
}

void rgp::SceneManager::changeScene(SceneEnum targetScene) {
	auto it = m_sceneMap.find(targetScene);

	if (it == m_sceneMap.end())
		throw std::runtime_error("Scene not found: " + std::to_string(targetScene));

	m_currentScene = std::move(it->second());
}

void rgp::SceneManager::updateCurrentScene() {
	if (m_currentScene.get())
		m_currentScene.get()->update();
}

void rgp::SceneManager::drawCurrentScene() {
	if (m_currentScene.get())
		m_currentScene.get()->draw();
}
