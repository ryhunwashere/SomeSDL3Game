#include <stdexcept>
#include "asset/asset_texture.h"

rgp::Texture::Texture(RendererEngine& renderer, const std::string& texturePath) :
    m_texturePtr([&renderer, &texturePath]() -> SDL_Texture* {
        SDL_Surface* surface = SDL_LoadPNG(texturePath.c_str());
        if (!surface)
            throw std::runtime_error(std::string("Texture surface creation error: ") + SDL_GetError());

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer.getRenderer(), surface);
        SDL_DestroySurface(surface);
        if (!texture)
            throw std::runtime_error(std::string("Texture creation error: ") + SDL_GetError());

        SDL_Log("Texture created");

        return texture;
    }()) {}

rgp::Texture::~Texture() {
    if (m_texturePtr) {
        SDL_DestroyTexture(m_texturePtr);
        SDL_Log("Texture destroyed.");
    }
}
