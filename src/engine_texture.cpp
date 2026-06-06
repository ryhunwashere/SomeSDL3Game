#include <SDL3/SDL.h>
#include <stdexcept>
#include "engine_texture.h"
#include "engine_renderer.h"
#include "struct_asset.h"

rgp::TextureEngine::~TextureEngine() {
	for (const auto& [path, textureInfo] : m_textureMap) {
		SDL_Log("Unloading texture: %s", textureInfo.path.c_str());
		SDL_DestroyTexture(textureInfo.texture);
	}

	SDL_Log("All textures succesfully unloaded.");
}

auto rgp::TextureEngine::loadPNGTexture(const std::string& path, float initialSize) -> const TextureInfo& {
    auto it = m_textureMap.find(path);
    if (it != m_textureMap.end()) return it->second;

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

    auto [insertedIt, success] = m_textureMap.insert_or_assign(
        path, 
        TextureInfo{ texture, path, initialSize }
    );

    return insertedIt->second;
}

void rgp::TextureEngine::unloadTexture(const TextureInfo& textureInfo) {
    SDL_DestroyTexture(textureInfo.texture);

    SDL_Log("Texture destroy from struct: %s", SDL_GetError());
    SDL_ClearError();

    m_textureMap.erase(textureInfo.path);
}

void rgp::TextureEngine::unloadTexture(const std::string& path) {
    auto it = m_textureMap.find(path);
    if (it == m_textureMap.end()) {
        SDL_Log("[WARN] Cannot unload texture due to not found: %s", path.c_str());
        return;
    }

    SDL_DestroyTexture(it->second.texture);

    SDL_Log("Texture destroy from path: %s", SDL_GetError());
    SDL_ClearError();

    m_textureMap.erase(path);
}

auto rgp::TextureEngine::getTexture(const std::string& path) -> const TextureInfo& {
	if (m_textureMap.find(path) == m_textureMap.end())
		throw std::runtime_error("PNG texture not found: " + path);

	return m_textureMap[path];
}