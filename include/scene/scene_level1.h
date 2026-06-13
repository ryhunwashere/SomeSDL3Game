#pragma once
#include <memory>

#include "game_context.h"
#include "scene.h"
#include "entity/entity_player.h"
#include "entity/entity_text.h"
#include "enum/enum_scenetype.h"

namespace rgp {
	class LevelOneScene : public Scene {
	public:
		explicit LevelOneScene(const GameContext& ctx);
		~LevelOneScene() override;

		auto update() -> SceneType override;
		void draw() override;

	private:
		std::unique_ptr<PlayerEntity> m_player;
		std::unique_ptr<TextEntity> m_text;
	};
}
