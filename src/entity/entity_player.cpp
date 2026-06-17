#include <string>
#include <complex>

#include "entity/entity_player.h"

#include "constant/constant.h"
#include "type/type_vector2f.h"
#include "manager/manager_time.h"

constexpr float TEXTURE_SIZE = 100.0f;
constexpr float MOVE_SPEED = 10.0f;

rgp::PlayerEntity::PlayerEntity(GameContext& ctx, const TextureType textureType, const AudioType audioType) :
	m_renderer(ctx.getRendererEngine()),
	m_input(ctx.getInputManager()),
	m_texturePtr(ctx.getTextureManager().getTexture(textureType)),
	m_shootTrack(std::make_unique<Track>(ctx.getAudioManager(), audioType, false)),
	m_nextShootTime(SDL_GetTicks())
{}

void rgp::PlayerEntity::draw() {
	const SDL_FRect dstRect{
		getX(),
		getY(),
		static_cast<float>(m_texturePtr->getTexturePtr()->w),
		static_cast<float>(m_texturePtr->getTexturePtr()->h)
	};

	m_renderer.drawTexture(constant::color::OPAQUE_F, &dstRect, m_texturePtr->getTexturePtr());
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
		m_shootTrack->play();
		m_nextShootTime = currentTime + s_cooldown;
	}
}
