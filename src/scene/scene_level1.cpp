#include <SDL3/SDL.h>
#include "scene/scene_level1.h"
#include "manager/manager_scene.h"
#include "constant/constant.h"
#include "factory/factory_text.h"

rgp::LevelOneScene::LevelOneScene(GameContext& ctx) : Scene(ctx),
	m_player(std::make_unique<PlayerEntity>(
		constant::PLAYER_ONE_SPRITE_PATH,
		m_ctx.renderer,
		m_ctx.textureEngine,
		m_ctx.inputEngine
	)),
	m_text(m_ctx.textFactory.create("test doang", FontType::ZenMaruMedium32))
{
	m_text->setPosition({5.0f, 5.0f});
	SDL_Log("Level 1 scene loaded.");
}

rgp::LevelOneScene::~LevelOneScene() {
	SDL_Log("Level 1 scene unloaded.");
}

auto rgp::LevelOneScene::update() -> SceneType {
	m_player->update();

	if (m_ctx.inputEngine.isKeyJustPressed(SDL_SCANCODE_P))
		return SceneType::MainMenu;

	return SceneType::Continue;
}

void rgp::LevelOneScene::draw() {
	m_ctx.renderer.draw(0.0, 0.0, 0.0, SDL_ALPHA_OPAQUE);
	m_player->draw();
	m_text->draw();
}
