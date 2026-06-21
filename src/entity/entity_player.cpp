#include <string>
#include <complex>

#include "entity/entity_bullet.h"
#include "entity/entity_player.h"
#include "type/type_vector2f.h"
#include "manager/manager_time.h"

constexpr float TEXTURE_SIZE = 100.0f;
constexpr float MOVE_SPEED = 10.0f;
constexpr uint64_t SHOOT_COOLDOWN = 80;

rgp::PlayerEntity::PlayerEntity(GameContext& ctx, BulletManager& bulletManager, const TextureType textureType, const AudioType audioType)
	:	m_bullet(
		ctx.getTextureManager().getTexture(TextureType::PlayerOneBulletSprite),
		-90.0,
		1.0f,
		3000.0f,
		BulletBehaviour::Linear),
		m_renderer(ctx.getRendererEngine()),
		m_input(ctx.getInputManager()),
		m_bulletMng(bulletManager),
		m_texturePtr(ctx.getTextureManager().getTexture(textureType)),
		m_shootTrack(std::make_unique<Track>(ctx.getAudioManager(), audioType, false)),
		m_nextShootTime(SDL_GetTicks())
{
	float playerW = 0.0f;
	float playerH = 0.0f;
	SDL_GetTextureSize(m_texturePtr->getTexturePtr(), &playerW, &playerH);
	setSize(playerW, playerH);

	float bulletW = 0.0f;
	float bulletH = 0.0f;
	SDL_GetTextureSize(m_bullet.texturePtr->getTexturePtr(), &bulletW, &bulletH);
	m_bullet.setSize(bulletW, bulletH);

	m_shootTrack->setGain(0.8f);
}

void rgp::PlayerEntity::draw() const {
	const SDL_FRect destRect = getFRect();
	m_renderer.drawTexture(&destRect, m_texturePtr->getTexturePtr());
}

void rgp::PlayerEntity::update() {
	updatePosition();
	updateShooting();
}

void rgp::PlayerEntity::updatePosition() {
	Vector2F dir = { 0.0f, 0.0f };

	if (m_input.isKeyDown(SDL_SCANCODE_A)) dir.x -= 1.0f;
	if (m_input.isKeyDown(SDL_SCANCODE_D)) dir.x += 1.0f;

	if (m_input.isKeyDown(SDL_SCANCODE_W)) dir.y -= 1.0f;
	if (m_input.isKeyDown(SDL_SCANCODE_S)) dir.y += 1.0f;

	if (const float length = std::sqrt(dir.x * dir.x + dir.y * dir.y); length > 1.0f) dir /= length;

	movePosition(dir * MOVE_SPEED);
}

void rgp::PlayerEntity::updateShooting() {
	if (const uint64_t currentTime = SDL_GetTicks();
		currentTime >= m_nextShootTime && m_input.isKeyDown(SDL_SCANCODE_L)) {

		Vector2F spawnPos1 = getTopLeft();
		Vector2F spawnPos2 = getTopMiddle();
		Vector2F spawnPos3 = getTopRight();

		spawnPos1.x -= m_bullet.getWidth() / 2.0f;
		spawnPos2.x -= m_bullet.getWidth() / 2.0f;
		spawnPos3.x -= m_bullet.getWidth() / 2.0f;

		m_bulletMng.spawnBullet(m_bullet, spawnPos1);
		m_bulletMng.spawnBullet(m_bullet, spawnPos2);
		m_bulletMng.spawnBullet(m_bullet, spawnPos3);

		m_shootTrack->play();
		m_nextShootTime = currentTime + SHOOT_COOLDOWN;
	}
}
