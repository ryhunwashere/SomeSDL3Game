#pragma once
#include <memory>
#include <array>
#include "scene.h"
#include "entity_text.h"
#include "manager_scene.h"

namespace rgp {
	class MainMenuScene : public Scene {
	public:
		MainMenuScene(SceneManager& sceneManager, InputEngine& inputEngine, RendererEngine& renderer);
		~MainMenuScene() override;

		void update() override;
		void draw() override;

	private:
		SceneManager& m_sceneManager;
		const double m_initTime;
		double m_now = 0.0;
	};
};