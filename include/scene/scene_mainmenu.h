#pragma once
#include "game_context.h"
#include "scene.h"

namespace rgp {
	class MainMenuScene : public Scene {
	public:
		explicit MainMenuScene(GameContext& ctx);
		~MainMenuScene() override;

		auto update() -> SceneType override;
		void draw() override;

	private:
		const double m_initTime;
		double m_now = 0.0;
	};
}
