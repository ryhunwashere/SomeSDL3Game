#include <string>
#include <stdexcept>
#include <cassert>
#include "entity_player.h"
#include "engine_texture.h"
#include "engine_renderer.h"
#include "engine_input.h"
#include "struct_vector2f.h"

constexpr float TEXTURE_SIZE = 100.0f;
constexpr float MOVE_SPEED = 10.0f;

rgp::PlayerEntity::PlayerEntity(const std::string& texturePath) : 
	m_textureAsset(&rgp::TextureEngine::get().loadPNGTexture(texturePath, TEXTURE_SIZE)) {}

rgp::PlayerEntity::~PlayerEntity() {
	if (m_textureAsset->texture) {
		SDL_Log("Unloading player texture...");
		rgp::TextureEngine::get().unloadTexture(m_textureAsset->path);
	}

	SDL_Log("Player entity unloaded.");
}

void rgp::PlayerEntity::draw() {
	assert(m_textureAsset->texture && "Texture for player is null");

	SDL_FRect dstRect{ 
		getX(),
		getY(),
		m_textureAsset->size,
		m_textureAsset->size
	};

	rgp::RendererEngine::get().draw(
		1.0, 1.0, 1.0, SDL_ALPHA_OPAQUE_FLOAT, m_textureAsset->texture, &dstRect
	);
}

void rgp::PlayerEntity::update() {
	updatePosition();
}

void rgp::PlayerEntity::updatePosition() {
	Vector2F dir = { 0.0f, 0.0f };

	auto& input = rgp::InputEngine::get();

	if (input.isKeyDown(SDL_SCANCODE_A)) dir.x -= 1.0f;
	if (input.isKeyDown(SDL_SCANCODE_D)) dir.x += 1.0f;

	if (input.isKeyDown(SDL_SCANCODE_W)) dir.y -= 1.0f;
	if (input.isKeyDown(SDL_SCANCODE_S)) dir.y += 1.0f;

	float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);

	if (length > 1.0f) dir /= length;

	movePosition(dir * MOVE_SPEED);
}