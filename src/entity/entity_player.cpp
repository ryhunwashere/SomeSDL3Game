#include <string>
#include <complex>

#include "entity/entity_bullet.h"
#include "entity/entity_player.h"

#include "event/event_player_lives_change.h"
#include "type/type_vector2f.h"
#include "manager/manager_time.h"

constexpr float TEXTURE_SIZE		= 100.0f;
constexpr float MOVE_SPEED			= 10.0f;
constexpr float MOVE_SPEED_SLOW		= 1.5f;
constexpr uint64_t SHOOT_COOLDOWN	= 80;

rgp::PlayerEntity::PlayerEntity(
	GameContext& ctx,
	BulletManager& bulletManager,
	const TextureType textureType,
	const AudioType audioType)
:	m_bullet(
		ctx.getTextureManager().getTexture(TextureType::PlayerOneBulletSprite),
		-90.0,
		1.0f,
		3000.0f,
		BulletBehaviour::Linear
	),
	m_shootTrack(Track(ctx.getAudioManager(), audioType, false)),
	m_ctx(ctx),
	m_bulletMng(bulletManager),
	m_texturePtr(ctx.getTextureManager().getTexture(textureType)),
	m_nextShootTime(SDL_GetTicks()),
	m_currentLives(3)
{
	float playerW = 0.0f;
	float playerH = 0.0f;
	SDL_GetTextureSize(m_texturePtr->getTexturePtr(), &playerW, &playerH);
	setSize(playerW, playerH);

	constexpr float HITBOX_RECT_LENGTH = 3.0f;

	m_hitbox = SDL_FRect{
		.x = getCenter().x - HITBOX_RECT_LENGTH/2.0f,
		.y = getCenter().y - HITBOX_RECT_LENGTH/2.0f,
		.w = HITBOX_RECT_LENGTH,
		.h = HITBOX_RECT_LENGTH,
	};

	float bulletW = 0.0f;
	float bulletH = 0.0f;
	SDL_GetTextureSize(m_bullet.texturePtr->getTexturePtr(), &bulletW, &bulletH);
	m_bullet.setSize(bulletW, bulletH);

	m_shootTrack.setGain(0.8f);

	m_ctx.getEventManager().publish<event::PlayerLivesChangeEvent>({
		.currentLives = std::max(m_currentLives, static_cast<int8_t>(0))
	});
}

void rgp::PlayerEntity::draw() const {
	const auto& renderer = m_ctx.getRendererEngine();

	const SDL_FRect destRect = getFRect();

	renderer.drawTexture(&destRect, m_texturePtr->getTexturePtr());

	if (m_isSlow)
		renderer.drawRect(constant::color::WHITE_OPAQUE_F, &m_hitbox);
}

void rgp::PlayerEntity::update() {
	if (m_ctx.getInputManager().isKeyJustPressed(SDL_SCANCODE_O)) {
		--m_currentLives;
		m_ctx.getEventManager().publish<event::PlayerLivesChangeEvent>({
			.currentLives = std::max(m_currentLives, static_cast<int8_t>(0))
		});
	}

	updatePosition();
	updateShooting();
}

void rgp::PlayerEntity::updatePosition() {
	const auto& input = m_ctx.getInputManager();
	Vector2F dir = { 0.0f, 0.0f };

	m_isSlow = input.isKeyDown(SDL_SCANCODE_LSHIFT);

	if (input.isKeyDown(SDL_SCANCODE_A)) dir.x -= 1.0f;
	if (input.isKeyDown(SDL_SCANCODE_D)) dir.x += 1.0f;

	if (input.isKeyDown(SDL_SCANCODE_W)) dir.y -= 1.0f;
	if (input.isKeyDown(SDL_SCANCODE_S)) dir.y += 1.0f;

	if (const float length = std::sqrt(dir.x * dir.x + dir.y * dir.y); length > 1.0f) dir /= length;

	const auto deltaPos = m_isSlow ? dir * MOVE_SPEED_SLOW : dir * MOVE_SPEED;

	movePosition(deltaPos);
	m_hitbox.x += deltaPos.x;
	m_hitbox.y += deltaPos.y;
}

void rgp::PlayerEntity::updateShooting() {
	if (const uint64_t currentTime = SDL_GetTicks();
		currentTime >= m_nextShootTime && m_ctx.getInputManager().isKeyDown(SDL_SCANCODE_L)) {

		Vector2F spawnPos1 = getTopLeft();
		Vector2F spawnPos2 = getTopMiddle();
		Vector2F spawnPos3 = getTopRight();

		spawnPos1.x -= m_bullet.getWidth() / 2.0f;
		spawnPos2.x -= m_bullet.getWidth() / 2.0f;
		spawnPos3.x -= m_bullet.getWidth() / 2.0f;

		m_bulletMng.spawnBullet(m_bullet, spawnPos1);
		m_bulletMng.spawnBullet(m_bullet, spawnPos2);
		m_bulletMng.spawnBullet(m_bullet, spawnPos3);

		m_shootTrack.play();
		m_nextShootTime = currentTime + SHOOT_COOLDOWN;
	}
}
