#pragma once
#include "game_context.h"
#include "scene.h"

namespace rgp {
	class MainMenuScene : public Scene {
	public:
		explicit MainMenuScene(const GameContext& ctx);
		~MainMenuScene() override;

		auto update() -> SceneType override;
		void draw() override;

	private:
		const float m_initTime;
		float m_now = 0.0f;
	};
}
