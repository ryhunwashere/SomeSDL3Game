#include <SDL3/SDL.h>
#include "scene/scene_level_one.h"

#include "constant/constant.h"
#include "manager/manager_scene.h"
#include "factory/factory_text.h"

rgp::LevelOneScene::LevelOneScene(GameContext& ctx) :
	Scene(ctx),
	m_player(std::make_unique<PlayerEntity>(ctx, TextureType::PlayerOneSprite, AudioType::PlayerShoot))
{
	SDL_Log("Level 1 scene loaded.");
}

rgp::LevelOneScene::~LevelOneScene() {
	m_ctx.getTextureManager().unloadTexture(TextureType::PlayerOneSprite);
	SDL_Log("Level 1 scene unloaded.");
}

void rgp::LevelOneScene::update() {
	m_player->update();

	if (m_ctx.getInputManager().isKeyJustPressed(SDL_SCANCODE_P))
		m_ctx.getEventManager().publish<event::SceneChangeEvent>({ .scene = SceneType::MainMenu });
}

void rgp::LevelOneScene::draw() {
	m_ctx.getRendererEngine().drawScreen(constant::color::BLACK_OPAQUE_F);
	m_player->draw();
}
