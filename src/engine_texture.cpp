#include <SDL3/SDL.h>
#include <stdexcept>
#include <memory>
#include "engine_texture.h"
#include "engine_renderer.h"
#include "asset_texture.h"

auto rgp::TextureEngine::loadPNG(const std::string &path, const float &initialSize) -> const std::shared_ptr<const TextureAsset> {
    if (auto existing = getTexture(path)) return existing;

    SDL_Surface* surface = SDL_LoadPNG(path.c_str());

    if (!surface)
        throw std::runtime_error(
            std::string("PNG load error: ") + SDL_GetError()
        );

    SDL_Texture* texture = SDL_CreateTextureFromSurface(
        RendererEngine::get().getRenderer(), 
        surface
    );

    SDL_DestroySurface(surface);

    if (!texture)
        throw std::runtime_error(
            std::string("PNG texture creation error: ") + SDL_GetError()
        );

    auto textureAsset = std::make_shared<TextureAsset>(texture, path, initialSize);

    m_textureMap[path] = textureAsset;

    return textureAsset;
}


auto rgp::TextureEngine::getTexture(const std::string& path) -> std::shared_ptr<const TextureAsset>{
    auto it = m_textureMap.find(path);

    if (it != m_textureMap.end()) {
        if (auto sharedAsset = it->second.lock()) return sharedAsset;
        m_textureMap.erase(it);
    }

    return nullptr;
}