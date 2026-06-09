#pragma once
#include <memory>
#include "scene.h"
#include "entity_player.h"
#include "manager_scene.h"
#include "engine_input.h"
#include "engine_renderer.h"
#include "engine_texture.h"

namespace rgp {
	class LevelOneScene : public Scene {
	public:
		LevelOneScene(SceneManager& sceneManager, InputEngine& inputEngine, RendererEngine& renderer, TextureEngine& textureEngine);
		~LevelOneScene() override;

		void update() override;
		void draw() override;

	private:
		SceneManager& m_sceneManager;
		std::unique_ptr<PlayerEntity> m_player;
	};
};