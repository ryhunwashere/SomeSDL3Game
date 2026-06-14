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

        return arr;
    }()) {}

rgp::TextureManager::~TextureManager() {
    m_textureMap.clear();
}

auto rgp::TextureManager::getTexture(TextureType type) -> std::shared_ptr<Texture> {
    if (const auto it = m_textureMap.find(type); it != m_textureMap.end()) {
        if (const auto sharedTex = it->second.lock()) {
            SDL_Log("Loading texture from cache...");
            return sharedTex;
        }
    }

    SDL_Log("Loading texture: %d", static_cast<int>(type));

    auto newTexture = std::make_shared<Texture>(m_renderer, m_texturePaths[static_cast<size_t>(type)]);
    m_textureMap[type] = newTexture;

    return newTexture;
}