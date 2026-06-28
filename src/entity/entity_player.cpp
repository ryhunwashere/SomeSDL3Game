#include <string>

#include "entity/entity_player.h"

#include <cmath>

#include "entity/entity_bullet.h"
#include "event/event_player_lives_change.h"
#include "type/type_vector2f.h"
#include "manager/manager_time.h"

constexpr float TEXTURE_SIZE			= 100.0f;
constexpr float MOVE_SPEED				= 1000.0f;
constexpr float MOVE_SPEED_SLOW			= 150.0f;
constexpr uint64_t SHOOT_COOLDOWN		= 80;
constexpr float COLLIDER_RADIUS			= 4.0f;
constexpr float GRAZE_COLLIDER_RADIUS	= 10.0f;

rgp::PlayerEntity::PlayerEntity(
	GameContext& ctx,
	BulletManager& bulletManager,
	const TextureType textureType,
	const AudioType audioType)
:	m_bulletMng(bulletManager),
	m_ctx(ctx),
	m_bullet(
		ctx.getTextureManager().getTexture(TextureType::PlayerOneBulletSprite),
		-90.0,
		1.0f,
		3000.0f,
		BulletBehaviour::Linear
	),
	m_shootTrack(Track(ctx.getAudioManager(), audioType, false)),
	m_collider{
		.x = getCenter().x,
		.y = getCenter().y,
		.r = COLLIDER_RADIUS,
	},
	m_grazeCollider{
		.x = getCenter().x,
		.y = getCenter().y,
		.r = GRAZE_COLLIDER_RADIUS,
	},
	m_texturePtr(ctx.getTextureManager().getTexture(textureType)),
	m_nextShootTime(SDL_GetTicks()),
	m_currentLives(3)
{
	float playerW = 0.0f;
	float playerH = 0.0f;
	SDL_GetTextureSize(m_texturePtr->getTexturePtr(), &playerW, &playerH);
	setSize(playerW, playerH);

	float bulletW = 0.0f;
	float bulletH = 0.0f;
	SDL_GetTextureSize(m_bullet.texturePtr->getTexturePtr(), &bulletW, &bulletH);
	m_bullet.setSize(bulletW, bulletH);

	m_shootTrack.setGain(0.8f);

	m_ctx.getEventManager().publish<event::PlayerLivesChangeEvent>({
		.currentLives = std::max(m_currentLives, static_cast<uint8_t>(0))
	});
}

void rgp::PlayerEntity::draw() const {
	auto& renderer = m_ctx.getRendererEngine();

	const SDL_FRect destRect = getFRect();

	renderer.drawTexture(&destRect, m_texturePtr->getTexturePtr());

	if (m_isSlow)
		renderer.drawCircleOutline(m_collider, 16, constant::color::WHITE_OPAQUE);
}

void rgp::PlayerEntity::update(const float dt) {
	updatePosition(dt);
	updateShooting(dt);
}

void rgp::PlayerEntity::updatePosition(const float dt) {
	const auto& input = m_ctx.getInputManager();
	Vector2F dir = { 0.0f, 0.0f };

	m_isSlow = input.isKeyDown(SDL_SCANCODE_LSHIFT);

	if (input.isKeyDown(SDL_SCANCODE_A)) dir.x -= 1.0f;
	if (input.isKeyDown(SDL_SCANCODE_D)) dir.x += 1.0f;
	if (input.isKeyDown(SDL_SCANCODE_W)) dir.y -= 1.0f;
	if (input.isKeyDown(SDL_SCANCODE_S)) dir.y += 1.0f;

	if (const float length = std::sqrt(dir.x * dir.x + dir.y * dir.y); length > 1.0f) dir /= length;

	Vector2F deltaPos = m_isSlow
		? dir * MOVE_SPEED_SLOW * dt
		: dir * MOVE_SPEED * dt;

	const float nextColliderX = m_collider.x + deltaPos.x;
	const float nextColliderY = m_collider.y + deltaPos.y;

	const float minX = m_collider.r;
	const float maxX = static_cast<float>(constant::dimension::VIEWPORT_WIDTH) - m_collider.r;
	const float minY = m_collider.r;
	const float maxY = static_cast<float>(constant::dimension::VIEWPORT_HEIGHT) - m_collider.r;

	const float clampedColliderX = std::clamp(nextColliderX, minX, maxX);
	const float clampedColliderY = std::clamp(nextColliderY, minY, maxY);

	deltaPos.x = clampedColliderX - m_collider.x;
	deltaPos.y = clampedColliderY - m_collider.y;

	movePosition(deltaPos);
}

void rgp::PlayerEntity::updateShooting(const float dt) {
	if (dt <= 0.0f) return;

	if (const uint64_t currentTime = SDL_GetTicks();
		currentTime >= m_nextShootTime && m_ctx.getInputManager().isKeyDown(SDL_SCANCODE_L)) {

		Vector2F spawnPos1 = getTopLeft();
		Vector2F spawnPos2 = getTopMiddle();
		Vector2F spawnPos3 = getTopRight();

		spawnPos1.x -= m_bullet.getWidth() / 2.0f;
		spawnPos2.x -= m_bullet.getWidth() / 2.0f;
		spawnPos3.x -= m_bullet.getWidth() / 2.0f;

		m_bulletMng.spawnPlayerBullet(m_bullet, spawnPos1);
		m_bulletMng.spawnPlayerBullet(m_bullet, spawnPos2);
		m_bulletMng.spawnPlayerBullet(m_bullet, spawnPos3);

		m_shootTrack.play();
		m_nextShootTime = currentTime + SHOOT_COOLDOWN;
	}
}
