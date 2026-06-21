#include <SDL3/SDL.h>
#include "scene/scene_level_one.h"

#include <format>

#include "constant/constant.h"
#include "manager/manager_scene.h"
#include "factory/factory_text.h"

rgp::LevelOneScene::LevelOneScene(GameContext& ctx) :
	Scene(ctx),
	m_bulletMng(m_ctx),
	m_player(std::make_unique<PlayerEntity>(m_ctx, m_bulletMng, TextureType::PlayerOneSprite, AudioType::PlayerShoot)),
	m_bulletCount(ctx.getTextFactory().create(FontType::ZenMaruMedium32Center, "Bullet Count: ")),
	m_music(std::make_unique<Track>(m_ctx.getAudioManager(), AudioType::LevelOneMusic, false))
{
	m_bulletCount->setPosition({0.0f, 40.0f});
	m_music->setGain(0.4f);
	m_music->play();
	SDL_Log("Level 1 scene loaded.");
}

rgp::LevelOneScene::~LevelOneScene() {
	m_music->stop();
	m_ctx.getTextureManager().unloadTexture(TextureType::PlayerOneSprite);
	m_ctx.getAudioManager().unloadAudio(AudioType::LevelOneMusic);
	SDL_Log("Level 1 scene unloaded.");
}

void rgp::LevelOneScene::update() {
	m_bulletCount->setText(std::format("Active bullets: {}", m_bulletMng.getActiveBulletsCount()));
	m_player->update();
	m_bulletMng.update();

	if (m_ctx.getInputManager().isKeyJustPressed(SDL_SCANCODE_ESCAPE))
		m_ctx.getEventManager().publish<event::SceneChangeEvent>({ .scene = SceneType::MainMenu });
}

void rgp::LevelOneScene::draw() {
	m_ctx.getRendererEngine().drawScreen(constant::color::BLACK_OPAQUE_F);
	m_player->draw();
	m_bulletMng.draw();
	m_bulletCount->draw();
}
