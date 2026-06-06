#pragma once
#include <SDL3/SDL.h>
#include <unordered_map>
#include <string>
#include "abstract_singleton.h"
#include "struct_asset.h"

namespace rgp {
    class TextureEngine : public Singleton<TextureEngine> {
        friend class Singleton<TextureEngine>;

    public:
        auto loadPNGTexture(const std::string& path, float initialSize) -> const TextureAsset&;

        void unloadTexture(const std::string& path);
        void unloadTexture(const TextureAsset& textureAsset);

        auto getTexture(const std::string& path) -> const TextureAsset&;

    private:
        TextureEngine() = default;
        ~TextureEngine();

        std::unordered_map<std::string, TextureAsset> m_textureMap;
    };
};