#pragma once
#include "scene.h"
#include "entity/entity_player.h"
#include "entity/entity_text.h"
#include "manager/manager_bullet.h"
#include "type/type_vector2f.h"

namespace rgp {
	class LevelOneScene final : public Scene {
	public:
		explicit LevelOneScene(GameContext& ctx);
		~LevelOneScene() override;

		void update(float dt) override;
		void fixedUpdate(float fixedDt) override;
		void draw(float alpha) override;

		[[nodiscard]] auto getBulletManager() -> BulletManager& { return m_bulletMng; }

	private:
		static constexpr float ENEMY_SHOOT_COOLDOWN = 0.1f;
		static constexpr float PLAYER_OFFSET_Y = 100.0f;

		const Vector2F SPAWN_POSITION{
			static_cast<float>(constant::dimension::VIEWPORT_WIDTH) / 2.0f,
			static_cast<float>(constant::dimension::VIEWPORT_HEIGHT) - PLAYER_OFFSET_Y
		};

		BulletManager m_bulletMng;
		PlayerEntity m_player;
		BulletEntity m_enemyBullet;
		TextEntity m_currentLivesText;
		SDL_Rect m_viewport;
		Track m_music;
		Circle m_circle;
		Texture* m_backgroundImg;
		float m_enemyShootCooldownTimer = 0.0f;
		bool m_isPaused = false;
	};
}
