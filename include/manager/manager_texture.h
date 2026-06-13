#pragma once
#include <unordered_map>
#include <array>
#include <memory>
#include "asset/asset_texture.h"
#include "engine/engine_renderer.h"
#include "enum/enum_texture_type.h"

namespace rgp {
    class TextureManager {
    public:
        explicit TextureManager(RendererEngine& renderer);
        ~TextureManager();

        auto getTexture(TextureType type) -> std::shared_ptr<Texture>;

    private:
        RendererEngine& m_renderer;
        const std::array<const char*, static_cast<size_t>(TextureType::Count)> m_texturePaths;
        std::unordered_map<TextureType, std::weak_ptr<Texture>> m_textureMap;
    };
}
