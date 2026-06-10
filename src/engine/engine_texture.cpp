#include <SDL3/SDL.h>
#include <stdexcept>
#include <memory>
#include "engine/engine_texture.h"
#include "engine/engine_renderer.h"

rgp::TextureEngine::TextureEngine(RendererEngine& renderer) : m_renderer(renderer) {
    SDL_Log("Texture engine loaded");
}

auto rgp::TextureEngine::loadPNG(const std::string &path, const float size) -> std::shared_ptr<const TextureAsset> {
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

    auto textureAsset = std::make_shared<TextureAsset>(texture, path, size);

    m_textureMap[path] = textureAsset;

    return textureAsset;
}


auto rgp::TextureEngine::getTexture(const std::string& path) -> std::shared_ptr<const TextureAsset>{
    if (const auto it = m_textureMap.find(path); it != m_textureMap.end()) {
        if (auto sharedAsset = it->second.lock()) return sharedAsset;
        m_textureMap.erase(it);
    }

    return nullptr;
}