#include "manager/manager_scene.h"

#include <SDL3/SDL.h>
#include <memory>
#include <cassert>
#include "scene/scene_main_menu.h"
#include "scene/scene_level_one.h"
#include "enum/enum_scenetype.h"

rgp::SceneManager::SceneManager(GameContext& ctx) : m_ctx(ctx) {
	m_sceneMap[SceneType::MainMenu] = [this] {
		return std::make_unique<MainMenuScene>(m_ctx);
	};

	m_sceneMap[SceneType::LevelOne] = [this] {
		return std::make_unique<LevelOneScene>(m_ctx);
	};

	changeScene(SceneType::MainMenu);

	SDL_Log("Scene manager loaded.");
}

rgp::SceneManager::~SceneManager() {
	SDL_Log("Scene manager unloaded.");
}

void rgp::SceneManager::changeScene(const SceneType targetScene) {
	assert(targetScene != SceneType::Continue && "'Continue' is not a valid scene");

	const auto it = m_sceneMap.find(targetScene);
	assert(it != m_sceneMap.end());
	assert(it->second);

	m_currentScene.reset();

	m_currentScene = it->second();
}

void rgp::SceneManager::updateCurrentScene() {
	if (!m_currentScene) return;

	switch (m_currentScene->update()) {
		case SceneType::MainMenu:
			return changeScene(SceneType::MainMenu);
		case SceneType::LevelOne:
			return changeScene(SceneType::LevelOne);
		default: break;
	}
}

void rgp::SceneManager::drawCurrentScene() const {
	if (m_currentScene) m_currentScene->draw();
}
