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

		void update(float dt) override;
		void draw() override;

		[[nodiscard]] auto getBulletManager() -> BulletManager& { return m_bulletMng; }

	private:
		static constexpr float ENEMY_SHOOT_COOLDOWN = 0.1f;

		BulletManager m_bulletMng;
		PlayerEntity m_player;
		BulletEntity m_enemyBullet;
		TextEntity m_currentLivesText;
		SDL_Rect m_viewport;
		Track m_music;
		Texture* m_backgroundImg;
		float m_enemyShootCooldownTimer = 0.0f;
		bool m_isPaused = false;
	};
}
