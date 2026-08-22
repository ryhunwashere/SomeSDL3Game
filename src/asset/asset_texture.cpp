#include <string>
#include "asset/asset_texture.h"

#include "except_sdl.h"
#include "engine/engine_renderer.h"

rgp::Texture::Texture(RendererEngine& renderer, std::string_view texturePath) :
    m_texturePtr([&renderer, &texturePath]() -> SDL_Texture* {
        SDL_Surface* surface = SDL_LoadPNG(texturePath.data());
        if (!surface)
            throw SDLException("Texture surface creation error");

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer.getRenderer(), surface);
        SDL_DestroySurface(surface);
        if (!texture)
            throw SDLException("Texture creation error");

        if (!SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_LINEAR))
            throw SDLException("Failed to set texture scale mode");

        if (!SDL_SetTextureColorModFloat(texture, 1.0f, 1.0f, 1.0f)
            || !SDL_SetTextureAlphaModFloat(texture, 1.0f))
            throw SDLException("Failed to set texture default color/alpha mod");

        SDL_Log("Texture created");

        return texture;
    }())
{
    if (!SDL_GetTextureSize(m_texturePtr, &m_textureWidth, &m_textureHeight)) [[unlikely]]
        throw SDLException("Failed to get texture sizes");
}

rgp::Texture::~Texture() {
    if (m_texturePtr) {
        SDL_DestroyTexture(m_texturePtr);
        SDL_Log("Texture destroyed.");
    }
}
