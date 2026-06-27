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

		void update(float dt) override;
		void draw() override;

	private:
		Track m_menuMusic;
		size_t m_selectedMenu = 0;
		float m_now = 0.0f;

		std::array<ButtonEntity, 3> m_buttonList;
		std::array<float, 3> m_buttonProgress{0.0f, 0.0f, 0.0f};

		void updateSelectedButton();
		void animateButtonWidths(float dt);
		void updateButtonColors();
	};
}
