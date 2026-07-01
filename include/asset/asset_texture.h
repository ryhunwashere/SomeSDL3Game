#pragma once
#include <SDL3/SDL.h>
#include <string_view>

namespace rgp {
    class RendererEngine;

    class Texture {
    public:
        Texture(RendererEngine& renderer, std::string_view texturePath);
        ~Texture();

        [[nodiscard]] auto getTexturePtr()      const -> SDL_Texture* { return m_texturePtr; }
        [[nodiscard]] auto getWidth()           const -> float        { return m_textureWidth; }
        [[nodiscard]] auto getHeight()          const -> float        { return m_textureHeight; }

        Texture(const Texture&)                               = delete;
        auto operator=(const Texture&) -> Texture&            = delete;

    private:
        SDL_Texture* m_texturePtr;
        float m_textureWidth  = 0.0f;
        float m_textureHeight = 0.0f;
    };
}
