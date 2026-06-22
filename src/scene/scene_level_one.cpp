#include <SDL3/SDL.h>
#include <format>
#include "scene/scene_level_one.h"
#include "manager/manager_scene.h"

rgp::LevelOneScene::LevelOneScene(GameContext& ctx) :
	Scene(ctx),
	m_viewport([&ctx]() -> SDL_Rect {
		constexpr int VIEWPORT_WIDTH  = 800;
		constexpr int VIEWPORT_HEIGHT = 1000;

		return SDL_Rect{
			.x = ctx.getRendererEngine().LOGICAL_WIDTH/2 - VIEWPORT_WIDTH/2,
			.y = (ctx.getRendererEngine().LOGICAL_HEIGHT - VIEWPORT_HEIGHT)/2,
			.w = VIEWPORT_WIDTH,
			.h = VIEWPORT_HEIGHT
		};
	}()),
	m_bulletMng(m_ctx),
	m_backgroundImg(m_ctx.getTextureManager().getTexture(TextureType::LevelOneBackground)),
	m_player(std::make_unique<PlayerEntity>(m_ctx, m_bulletMng, TextureType::PlayerOneSprite, AudioType::PlayerShoot)),
	m_bulletCountText(std::make_unique<TextEntity>(m_ctx, FontType::ZenMaruMedium32Left, "Active bullets: ")),
	m_currentLivesText(std::make_unique<TextEntity>(m_ctx, FontType::ZenMaruMedium32Left, "Lives: ")),
	m_music(std::make_unique<Track>(m_ctx.getAudioManager(), AudioType::LevelOneMusic, false))
{
	constexpr float UI_X_OFFSET = 50.0f;

	m_bulletCountText->setPosition({
		static_cast<float>(m_viewport.x + m_viewport.w) + UI_X_OFFSET,
		40.0f
	});
	m_bulletCountText->setColor(constant::color::WHITE_OPAQUE);

	m_currentLivesText->setPosition({
		static_cast<float>(m_viewport.x + m_viewport.w) + UI_X_OFFSET,
		80.0f
	});
	m_currentLivesText->setColor(constant::color::WHITE_OPAQUE);

	m_ctx.getEventManager().subscribe<event::PlayerLivesChangeEvent>([this](const event::PlayerLivesChangeEvent& e) -> void {
		if (e.currentLives > 0)
			m_currentLivesText->setText(std::format("Lives: {}", e.currentLives));
		else
			m_ctx.getEventManager().publish<event::SceneChangeEvent>({.scene = SceneType::MainMenu});
	});

	m_music->setGain(0.4f);
	m_music->play();
	SDL_Log("Level 1 scene loaded.");
}

rgp::LevelOneScene::~LevelOneScene() {
	m_music->stop();
	m_ctx.getAudioManager().unloadAudio(AudioType::LevelOneMusic);
	m_ctx.getTextureManager().unloadTexture(TextureType::PlayerOneSprite);
	m_ctx.getTextureManager().unloadTexture(TextureType::LevelOneBackground);
	SDL_Log("Level 1 scene unloaded.");
}

void rgp::LevelOneScene::update() {
	m_bulletCountText->setText(std::format("Active bullets: {}", m_bulletMng.getActiveBulletsCount()));
	m_player->update();
	m_bulletMng.update();

	if (m_ctx.getInputManager().isKeyJustPressed(SDL_SCANCODE_ESCAPE))
		m_ctx.getEventManager().publish<event::SceneChangeEvent>({ .scene = SceneType::MainMenu });
}

void rgp::LevelOneScene::draw() {
	m_ctx.getRendererEngine().drawScreen(m_backgroundImg->getTexturePtr());
	m_bulletCountText->draw();
	m_currentLivesText->draw();

	m_ctx.getRendererEngine().drawViewport(&m_viewport, [this]() -> void {
		m_ctx.getRendererEngine().drawScreen(constant::color::BLACK_OPAQUE_F);
		m_player->draw();
		m_bulletMng.draw();
	});
}
