#pragma once
#include <memory>

#include "game_context.h"
#include "scene.h"
#include "entity/entity_player.h"
#include "entity/entity_text.h"
#include "manager/manager_bullet.h"

namespace rgp {
	class LevelOneScene final : public Scene {
	public:
		explicit LevelOneScene(GameContext& ctx);
		~LevelOneScene() override;

		void update() override;
		void draw() override;

		[[nodiscard]] auto getBulletManager() -> BulletManager& { return m_bulletMng; }

	private:
		BulletManager m_bulletMng;
		std::unique_ptr<PlayerEntity> m_player;
		std::unique_ptr<TextEntity> m_bulletCount;
		std::unique_ptr<Track> m_music;
	};
}
