#include "manager/manager_scene.h"

#include <SDL3/SDL.h>
#include <memory>
#include <cassert>
#include <format>

#include "constant/constant.h"
#include "scene/scene_main_menu.h"
#include "scene/scene_level_one.h"
#include "enum/enum_scenetype.h"

rgp::SceneManager::SceneManager(GameContext& ctx) : m_ctx(ctx),
	m_fpsText(ctx.getTextFactory().create(FontType::ZenMaruMedium32Left, "FPS: "))
{
	m_sceneMap[SceneType::MainMenu] = [this] {
		return std::make_unique<MainMenuScene>(m_ctx);
	};

	m_sceneMap[SceneType::LevelOne] = [this] {
		return std::make_unique<LevelOneScene>(m_ctx);
	};

	m_fpsText->setColor(constant::color::WHITE_OPAQUE);

	changeScene(SceneType::MainMenu);

	SDL_Log("Scene manager loaded.");
}

rgp::SceneManager::~SceneManager() {
	SDL_Log("Scene manager unloaded.");
}

void rgp::SceneManager::changeScene(const SceneType targetScene) {
	if (targetScene == SceneType::Continue) return;

	const auto it = m_sceneMap.find(targetScene);
	assert(it != m_sceneMap.end());
	assert(it->second);

	m_currentScene.reset();

	m_currentScene = it->second();
}

auto rgp::SceneManager::updateCurrentScene() -> bool {
	m_fpsText->setText("FPS: " + std::to_string(static_cast<uint64_t>(m_ctx.getTimeManager().getCurrentFps())));

	if (!m_currentScene) return false;

	const SceneType targetScene = m_currentScene->update();

	if (targetScene == SceneType::Exit) return false;

	changeScene(targetScene);
	return true;
}

void rgp::SceneManager::drawCurrentScene() const {
	if (m_currentScene) m_currentScene->draw();
	m_fpsText->draw();
}