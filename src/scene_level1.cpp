#include <SDL3/SDL.h>
#include "scene_level1.h"
#include "manager_scene.h"
#include "engine_input.h"
#include "engine_renderer.h"

rgp::LevelOneScene::LevelOneScene() {
	m_player = std::make_unique<rgp::PlayerEntity>("player1_sprite.png");

	SDL_Log("Level 1 scene loaded.");
}

rgp::LevelOneScene::~LevelOneScene() {
	SDL_Log("Level 1 scene unloaded.");
}

void rgp::LevelOneScene::update() {
	m_player->update();

	if (rgp::InputEngine::get().isKeyJustPressed(SDL_SCANCODE_P))
		rgp::SceneManager::get().changeScene(SceneManager::MAIN_MENU);
}

void rgp::LevelOneScene::draw() {
	rgp::RendererEngine::get().draw(0.0, 0.0, 0.0, SDL_ALPHA_OPAQUE);
	m_player->draw();
}