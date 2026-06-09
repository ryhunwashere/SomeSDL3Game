#pragma once
#include <SDL3/SDL.h>
#include <unordered_map>
#include <string>
#include <memory>
#include "asset_texture.h"
#include "engine_renderer.h"

namespace rgp {
    class TextureEngine {
    public:
        TextureEngine(RendererEngine& renderer);
        ~TextureEngine() = default;

        auto loadPNG(const std::string& path, const float& size) -> const std::shared_ptr<const TextureAsset>;
        auto getTexture(const std::string& path) -> std::shared_ptr<const TextureAsset>;

        void clearExpiredEntries() {
            std::erase_if(
                m_textureMap, [](const auto& item) { return item.second.expired(); }
            );
        }

    private:
        RendererEngine& m_renderer;
        std::unordered_map<std::string, std::weak_ptr<const TextureAsset>> m_textureMap;
    };
};