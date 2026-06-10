#pragma once
#include "scene.h"

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
}