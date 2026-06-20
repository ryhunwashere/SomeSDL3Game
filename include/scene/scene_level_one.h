#pragma once
#include <memory>

#include "game_context.h"
#include "scene.h"
#include "entity/entity_player.h"

namespace rgp {
	class LevelOneScene final : public Scene {
	public:
		explicit LevelOneScene(GameContext& ctx);
		~LevelOneScene() override;

		void update() override;
		void draw() override;

	private:
		std::unique_ptr<PlayerEntity> m_player;
	};
}
