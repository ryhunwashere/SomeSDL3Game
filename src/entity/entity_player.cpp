#include <string>
#include <complex>

#include "entity/entity_player.h"
#include "engine/engine_renderer.h"
#include "manager/manager_texture.h"
#include "manager/manager_input.h"
#include "type/type_vector2f.h"

constexpr float TEXTURE_SIZE = 100.0f;
constexpr float MOVE_SPEED = 10.0f;

rgp::PlayerEntity::PlayerEntity(
	RendererEngine& renderer,
	InputManager& input,
	TextureManager& textureManager,
	const TextureType textureType)
:
	m_renderer(renderer),
	m_input(input),
	m_texture(textureManager.getTexture(textureType)) {}

void rgp::PlayerEntity::draw() {
	const SDL_FRect dstRect{
		getX(),
		getY(),
		static_cast<float>(m_texture->getTexturePtr()->w),
		static_cast<float>(m_texture->getTexturePtr()->h)
	};

	m_renderer.draw(1.0, 1.0, 1.0, SDL_ALPHA_OPAQUE_FLOAT, m_texture->getTexturePtr(), &dstRect);
}

void rgp::PlayerEntity::update() {
	updatePosition();
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