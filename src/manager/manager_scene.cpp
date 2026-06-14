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
	m_fpsText(ctx.getTextFactory().create(FontType::ZenMaruMedium32, "FPS: "))
{
	m_sceneMap[SceneType::MainMenu] = [this] {
		return std::make_unique<MainMenuScene>(m_ctx);
	};

	m_sceneMap[SceneType::LevelOne] = [this] {
		return std::make_unique<LevelOneScene>(m_ctx);
	};

	m_fpsText->setColor({ 85.0f, 255.0f, 28.0f, 255.0f });

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
	updateFpsText();

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
	m_fpsText->draw();
}

void rgp::SceneManager::updateFpsText() {
	const auto currentTime = SDL_GetPerformanceCounter();
	const auto frameTicks = currentTime - m_lastTime;
	m_lastTime = currentTime;

	// prevent division by zero if delta is somehow 0
	if (const float deltaTime = static_cast<float>(frameTicks) / static_cast<float>(m_frequency); deltaTime > 0.0f) {
		const float rawFps = 1.0f / deltaTime;

		m_smoothedFps = s_alpha * rawFps + (1.0f - s_alpha) * m_smoothedFps;

		const int displayFps = static_cast<int>(m_smoothedFps);

		m_fpsText->setText("FPS: " + std::format("{}", displayFps));
	}
}