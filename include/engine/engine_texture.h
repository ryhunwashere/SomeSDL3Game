#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include "asset/asset_texture.h"
#include "engine_renderer.h"

namespace rgp {
    class TextureEngine {
    public:
        explicit TextureEngine(const RendererEngine& renderer);
        ~TextureEngine();

        auto loadPNG(const std::string& path, float size) -> std::shared_ptr<const TextureAsset>;
        auto getTexture(const std::string& path) -> std::shared_ptr<const TextureAsset>;

    private:
        const RendererEngine& m_renderer;
        std::unordered_map<std::string, std::weak_ptr<const TextureAsset>> m_textureMap;
    };
}