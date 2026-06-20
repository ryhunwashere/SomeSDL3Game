#pragma once
#include "game_context.h"
#include "scene.h"
#include "asset/asset_track.h"
#include "entity/entity_button.h"

namespace rgp {
	class MainMenuScene final : public Scene {
	public:
		explicit MainMenuScene(GameContext& ctx);
		~MainMenuScene() override;

		void update() override;
		void draw() override;

	private:
		size_t m_selectedMenu = 0;
		float m_now = 0.0f;
		std::unique_ptr<Track> m_menuMusic;
		std::unique_ptr<TextEntity> m_musicStatusText;

		std::array<std::unique_ptr<ButtonEntity>, 3> m_buttonList;
		std::array<float, 3> m_buttonProgress{0.0f, 0.0f, 0.0f};

		void updateSelectedButton();
		void animateButtonWidths(float dt);
		void updateButtonColors() const;
	};
}
