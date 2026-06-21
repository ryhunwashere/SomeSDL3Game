#include <SDL3/SDL.h>
#include <memory>
#include "manager/manager_texture.h"
#include "constant/constant.h"
#include "engine/engine_renderer.h"

rgp::TextureManager::TextureManager(RendererEngine& renderer) :
    m_renderer(renderer),
    m_texturePaths([]() -> std::array<const char*, static_cast<size_t>(TextureType::Count)> {
        std::array<const char*, static_cast<size_t>(TextureType::Count)> arr{};

        arr[static_cast<size_t>(TextureType::PlayerOneSprite)] = constant::path::PLAYER_ONE_SPRITE_PATH;
        arr[static_cast<size_t>(TextureType::PlayerOneBulletSprite)] = constant::path::PLAYER_ONE_BULLET_SPRITE_PATH;
        arr[static_cast<size_t>(TextureType::LevelOneBackground)] = constant::path::LEVEL_ONE_BACKGROUND_IMG_PATH;

        return arr;
    }()) {}

auto rgp::TextureManager::getTexture(TextureType type) -> Texture* {
    const auto index = static_cast<size_t>(type);

    if (m_textureCache[index]) {
        SDL_Log("Loading texture from cache: %zu", index);
        return m_textureCache[index].get();
    }

    SDL_Log("Loading and caching texture: %zu", index);
    m_textureCache[index] = std::make_unique<Texture>(m_renderer, m_texturePaths[index]);
    return m_textureCache[index].get();
}

void rgp::TextureManager::unloadTexture(TextureType type) {
    if (const auto index = static_cast<size_t>(type); m_textureCache[index]) {
        SDL_Log("Unloading texture: %d", static_cast<int>(type));
        m_textureCache[index].reset();
    }
}