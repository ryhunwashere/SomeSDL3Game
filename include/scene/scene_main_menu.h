#pragma once
#include "game_context.h"
#include "scene.h"
#include "asset/asset_track.h"

namespace rgp {
	class MainMenuScene final : public Scene {
	public:
		explicit MainMenuScene(GameContext& ctx);
		~MainMenuScene() override;

		auto update() -> SceneType override;
		void draw() override;

	private:
		float m_now = 0.0f;
		std::unique_ptr<Track> m_menuMusic;
		std::unique_ptr<TextEntity> m_musicStatusText;
	};
}
