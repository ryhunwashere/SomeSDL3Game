#include <SDL3/SDL.h>
#include "scene/scene_level_one.h"
#include "manager/manager_scene.h"
#include "factory/factory_text.h"

rgp::LevelOneScene::LevelOneScene(GameContext& ctx) : Scene(ctx),
	m_player(std::make_unique<PlayerEntity>(
		ctx.getRendererEngine(),
		ctx.getInputManager(),
		ctx.getTextureManager(),
		TextureType::PlayerOneSprite)),
	m_text(ctx.getTextFactory().create("test ajah", FontType::ZenMaruMedium32))
{
	m_text->setPosition({5.0f, 5.0f});
	SDL_Log("Level 1 scene loaded.");
}

rgp::LevelOneScene::~LevelOneScene() {
	SDL_Log("Level 1 scene unloaded.");
}

auto rgp::LevelOneScene::update() -> SceneType {
	m_player->update();

	if (m_ctx.getInputManager().isKeyJustPressed(SDL_SCANCODE_P))
		return SceneType::MainMenu;

	return SceneType::Continue;
}

void rgp::LevelOneScene::draw() {
	m_ctx.getRendererEngine().draw(0.0, 0.0, 0.0, SDL_ALPHA_OPAQUE);
	m_player->draw();
	m_text->draw();
}
