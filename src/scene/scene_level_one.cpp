#include <SDL3/SDL.h>
#include <format>
#include "scene/scene_level_one.h"
#include "manager/manager_scene.h"
#include "util/util_intersect.h"

rgp::LevelOneScene::LevelOneScene(GameContext& ctx) :
	Scene(ctx),
	m_bulletMng(m_ctx),
	m_player(PlayerEntity(m_ctx, m_bulletMng, TextureType::PlayerOneSprite, AudioType::PlayerShoot)),
	m_enemyBullet(
		BulletEntity(
			m_ctx.getTextureManager().getTexture(TextureType::CircleBulletSprite),
			90.0f,
			5.0f,
			500.0f,
			BulletBehaviour::Linear
		)),
	m_currentLivesText(TextEntity(m_ctx, FontType::ZenMaruMedium32Left, "Lives: ")),
	m_viewport(SDL_Rect{
		.x = RendererEngine::LOGICAL_WIDTH/2 - constant::dimension::VIEWPORT_WIDTH/2,
		.y = (RendererEngine::LOGICAL_HEIGHT - constant::dimension::VIEWPORT_HEIGHT)/2,
		.w = constant::dimension::VIEWPORT_WIDTH,
		.h = constant::dimension::VIEWPORT_HEIGHT,
	}),
	m_music(Track(m_ctx.getAudioManager(), AudioType::LevelOneMusic, false)),
	m_circle(Circle{50.0f, 200.0f, 50.0f}),
	m_backgroundImg(m_ctx.getTextureManager().getTexture(TextureType::LevelOneBackground))
{
	constexpr float UI_OFFSET_X = 50.0f;
	constexpr float UI_OFFSET_Y = 80.0f;

	m_currentLivesText.setPosition({
		static_cast<float>(m_viewport.x + m_viewport.w) + UI_OFFSET_X,
		UI_OFFSET_Y
	});
	m_currentLivesText.setColor(constant::color::WHITE_OPAQUE);

	auto& eventMng = m_ctx.getEventManager();

	eventMng.subscribe<event::PlayerLivesChangeEvent>([this](const auto& e) -> void {
		if (e.currentLives > 0) {
			m_bulletMng.clearEnemyBullets();
			m_player.setCurrentLives(e.currentLives);
			m_currentLivesText.setText(std::format("Lives: {}", e.currentLives));
		} else {
			m_ctx.getEventManager().publish<event::SceneChangeEvent>({.scene = SceneType::MainMenu});
		}
	});

	m_player.setPosition(SPAWN_POSITION);

	float enemyBulletW = 0.0f;
	float enemyBulletH = 0.0f;
	SDL_GetTextureSize(m_enemyBullet.texturePtr->getTexturePtr(), &enemyBulletW, &enemyBulletH);
	m_enemyBullet.setSize(enemyBulletW, enemyBulletH);

	m_music.setGain(0.4f);
	m_music.play();

	SDL_Log("Level 1 scene loaded.");
}

rgp::LevelOneScene::~LevelOneScene() {
	m_music.stop();
	m_ctx.getAudioManager().unloadAudio(AudioType::LevelOneMusic);
	m_ctx.getTextureManager().unloadTexture(TextureType::PlayerOneSprite);
	m_ctx.getTextureManager().unloadTexture(TextureType::LevelOneBackground);
	SDL_Log("Level 1 scene unloaded.");
}

void rgp::LevelOneScene::update(const float dt) {
	const float deltaTime = m_isPaused ? 0.0f : dt;
	m_player.update(deltaTime);
	m_bulletMng.update(deltaTime);

	const auto& input = m_ctx.getInputManager();

	if (input.isKeyJustPressed(SDL_SCANCODE_SPACE)) {
		m_isPaused = !m_isPaused;
		if (m_music.isPlaying()) m_music.pause();
		else m_music.resume();
	}

	auto& eventMng = m_ctx.getEventManager();

	if (input.isKeyJustPressed(SDL_SCANCODE_ESCAPE))
		eventMng.publish<event::SceneChangeEvent>({ .scene = SceneType::MainMenu });

	if (m_isPaused) return;

	// test collision & invoke player lives changed event
	if (util::intersect::hasIntersection(m_player.getCollider(), m_circle)) {
		m_player.setPosition(SPAWN_POSITION);
		const uint8_t updatedCurrentLives = m_player.getCurrentLives() - 1;
		eventMng.publish<event::PlayerLivesChangeEvent>({ .currentLives = updatedCurrentLives });
	}

	m_enemyShootCooldownTimer -= deltaTime;

	if (m_enemyShootCooldownTimer <= 0.0f) {
		constexpr float X_OFFSET = 20.0f;
		constexpr float Y_OFFSET = 50.0f;

		const Vector2F spawnPos1{
			static_cast<float>(constant::dimension::VIEWPORT_WIDTH) / 2.0f - X_OFFSET * 2,
			Y_OFFSET
		 };
		const Vector2F spawnPos2{
			static_cast<float>(constant::dimension::VIEWPORT_WIDTH) / 2.0f - X_OFFSET,
			Y_OFFSET
		 };
		const Vector2F spawnPos3{
			static_cast<float>(constant::dimension::VIEWPORT_WIDTH) / 2.0f,
			Y_OFFSET
		 };
		const Vector2F spawnPos4{
			static_cast<float>(constant::dimension::VIEWPORT_WIDTH) / 2.0f + X_OFFSET,
			Y_OFFSET
		 };
		const Vector2F spawnPos5{
			static_cast<float>(constant::dimension::VIEWPORT_WIDTH) / 2.0f + X_OFFSET * 2,
			Y_OFFSET
		 };

		m_bulletMng.spawnEnemyBullet(m_enemyBullet, spawnPos1);
		m_bulletMng.spawnEnemyBullet(m_enemyBullet, spawnPos2);
		m_bulletMng.spawnEnemyBullet(m_enemyBullet, spawnPos3);
		m_bulletMng.spawnEnemyBullet(m_enemyBullet, spawnPos4);
		m_bulletMng.spawnEnemyBullet(m_enemyBullet, spawnPos5);

		m_enemyShootCooldownTimer += ENEMY_SHOOT_COOLDOWN;
	}
}

void rgp::LevelOneScene::draw() {
	m_ctx.getRendererEngine().drawScreen(m_backgroundImg->getTexturePtr());
	m_currentLivesText.draw();

	m_ctx.getRendererEngine().drawViewport(&m_viewport, [this]() -> void {
		m_ctx.getRendererEngine().drawScreen(constant::color::BLACK_OPAQUE_F);
		m_player.draw();
		m_bulletMng.draw();
		m_ctx.getRendererEngine().drawCircleOutline(m_circle, 16, constant::color::WHITE_OPAQUE);

		if (m_isPaused)
			m_ctx.getRendererEngine().drawScreen({0.0f, 0.0f, 0.0f, 0.5f});
	});
}
