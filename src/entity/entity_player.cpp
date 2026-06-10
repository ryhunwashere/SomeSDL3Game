#include <string>
#include <cassert>
#include "../../include/entity/entity_player.h"

#include <complex>

#include "engine/engine_texture.h"
#include "engine/engine_renderer.h"
#include "engine/engine_input.h"
#include "type/type_vector2f.h"

constexpr float TEXTURE_SIZE = 100.0f;
constexpr float MOVE_SPEED = 10.0f;

rgp::PlayerEntity::PlayerEntity(
	const std::string& texturePath,
	RendererEngine& renderer,
	TextureEngine& textureEngine,
	InputEngine& inputEngine
) :
	m_renderer(renderer),
	m_textureEngine(textureEngine),
	m_input(inputEngine),
	m_textureAsset(m_textureEngine.loadPNG(texturePath, TEXTURE_SIZE)) {}

void rgp::PlayerEntity::draw() {
	assert(m_textureAsset->texture && "Texture for player is null");

	const SDL_FRect dstRect{
		getX(),
		getY(),
		m_textureAsset->size,
		m_textureAsset->size
	};

	m_renderer.draw(1.0, 1.0, 1.0, SDL_ALPHA_OPAQUE_FLOAT, m_textureAsset->texture, &dstRect);
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