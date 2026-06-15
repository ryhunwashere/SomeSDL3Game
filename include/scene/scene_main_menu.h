#pragma once
#include "game_context.h"
#include "scene.h"
#include "entity/entity_track.h"

namespace rgp {
	class MainMenuScene final : public Scene {
	public:
		explicit MainMenuScene(GameContext& ctx);
		~MainMenuScene() override;

		auto update() -> SceneType override;
		void draw() override;

	private:
		float m_now = 0.0f;
		std::unique_ptr<TrackEntity> m_menuMusic;
	};
}
