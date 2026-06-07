#pragma once
#include <SDL3/SDL.h>
#include <unordered_map>
#include <string>
#include <memory>
#include "abstract_singleton.h"
#include "struct_asset_texture.h"

namespace rgp {
    class TextureEngine : public Singleton<TextureEngine> {
        friend class Singleton<TextureEngine>;

    public:
        auto loadPNG(const std::string& path, const float &initialSize) -> const std::shared_ptr<const TextureAsset>;
        auto getTexture(const std::string& path) -> std::shared_ptr<const TextureAsset>;

        void clearExpiredEntries() {
            std::erase_if(
                m_textureMap, [](const auto& item) { return item.second.expired(); }
            );
        }

    private:
        TextureEngine()  = default;
        ~TextureEngine() = default;

        std::unordered_map<std::string, std::weak_ptr<const TextureAsset>> m_textureMap;
    };
};