#pragma once
#include <SDL3/SDL.h>

#include "engine/engine_renderer.h"

namespace rgp {
    class Texture {
    public:
        Texture(RendererEngine& renderer, std::string_view texturePath);
        ~Texture();

        [[nodiscard]] auto getTexturePtr() const -> SDL_Texture* { return m_texturePtr; }

        Texture(const Texture&)                               = delete;
        auto operator=(const Texture&) -> Texture&            = delete;

    private:
        SDL_Texture* m_texturePtr;
    };
}
