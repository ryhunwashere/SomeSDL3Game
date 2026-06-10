#include <SDL3/SDL.h>
#include "scene/scene_level1.h"
#include "manager/manager_scene.h"
#include "engine/engine_input.h"
#include "engine/engine_renderer.h"

rgp::LevelOneScene::LevelOneScene(SceneManager& sceneManager, InputEngine& inputEngine, RendererEngine& renderer, TextureEngine& textureEngine) :
	Scene(sceneManager, inputEngine, renderer), 
	m_sceneManager(sceneManager),
	m_player(std::make_unique<PlayerEntity>(
		"player1_sprite.png",
		renderer,
		textureEngine,
		inputEngine
	))
{
	SDL_Log("Level 1 scene loaded.");
}

rgp::LevelOneScene::~LevelOneScene() {
	SDL_Log("Level 1 scene unloaded.");
}

void rgp::LevelOneScene::update() {
	m_player->update();

	if (m_inputEngine.isKeyJustPressed(SDL_SCANCODE_P))
		m_sceneManager.changeScene(SceneManager::MAIN_MENU);
}

void rgp::LevelOneScene::draw() {
	m_renderer.draw(0.0, 0.0, 0.0, SDL_ALPHA_OPAQUE);
	m_player->draw();
}