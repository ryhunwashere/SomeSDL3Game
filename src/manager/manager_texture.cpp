#include <SDL3/SDL.h>
#include <stdexcept>
#include <memory>
#include "manager/manager_texture.h"
#include "engine/engine_renderer.h"

rgp::TextureManager::TextureManager(const RendererEngine& renderer) : m_renderer(renderer) {
    SDL_Log("Texture manager loaded");
}

rgp::TextureManager::~TextureManager() {
    std::erase_if(m_textureMap, [](const auto& item) { return item.second.expired(); } );
}

auto rgp::TextureManager::loadPNG(const std::string &path, const float size) -> std::shared_ptr<const Texture> {
    if (auto existing = getTexture(path)) return existing;

    SDL_Surface* surface = SDL_LoadPNG(path.c_str());

    if (!surface)
        throw std::runtime_error(
            std::string("PNG load error: ") + SDL_GetError()
        );

    SDL_Texture* texture = SDL_CreateTextureFromSurface(
        m_renderer.getRenderer(),
        surface
    );

    SDL_DestroySurface(surface);

    if (!texture)
        throw std::runtime_error(
            std::string("PNG texture creation error: ") + SDL_GetError()
        );

    auto textureAsset = std::make_shared<Texture>(texture, path, size);

    m_textureMap[path] = textureAsset;

    return textureAsset;
}


auto rgp::TextureManager::getTexture(const std::string& path) -> std::shared_ptr<const Texture>{
    if (const auto it = m_textureMap.find(path); it != m_textureMap.end()) {
        if (auto sharedAsset = it->second.lock()) return sharedAsset;
        m_textureMap.erase(it);
    }

    return nullptr;
}