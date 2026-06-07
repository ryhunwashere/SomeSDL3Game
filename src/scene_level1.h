#pragma once
#include <memory>
#include "scene.h"
#include "entity_player.h"

namespace rgp {
	class LevelOneScene : public Scene {
	public:
		LevelOneScene();
		~LevelOneScene() override;

		void update() override;
		void draw() override;

	private:
		std::unique_ptr<PlayerEntity> m_player;
	};
};