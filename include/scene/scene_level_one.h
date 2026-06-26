#pragma once

#include "game_context.h"
#include "scene.h"
#include "entity/entity_player.h"
#include "entity/entity_text.h"
#include "manager/manager_bullet.h"

namespace rgp {
	class LevelOneScene final : public Scene {
	public:
		static constexpr int VIEWPORT_WIDTH  = 800;
		static constexpr int VIEWPORT_HEIGHT = 1000;

		explicit LevelOneScene(GameContext& ctx);
		~LevelOneScene() override;

		void update() override;
		void draw() override;

		[[nodiscard]] auto getBulletManager() -> BulletManager& { return m_bulletMng; }

	private:
		BulletManager m_bulletMng;
		PlayerEntity m_player;
		TextEntity m_currentLivesText;
		SDL_Rect m_viewport;
		Track m_music;
		Texture* m_backgroundImg;
	};
}
