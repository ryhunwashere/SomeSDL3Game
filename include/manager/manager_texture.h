#pragma once
#include <array>
#include <memory>
#include "asset/asset_texture.h"
#include "engine/engine_renderer.h"
#include "enum/enum_texture_type.h"

namespace rgp {
    class TextureManager {
    public:
        explicit TextureManager(RendererEngine& renderer);
        ~TextureManager() = default;

        auto getTexture(TextureType type) -> Texture*;
        void unloadTexture(TextureType type);

    private:
        RendererEngine& m_renderer;
        const std::array<const char*, static_cast<size_t>(TextureType::Count)> m_texturePaths;
        std::array<std::unique_ptr<Texture>, static_cast<size_t>(TextureType::Count)> m_textureCache;
    };
}
