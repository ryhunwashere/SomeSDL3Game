#pragma once
#include <SDL3/SDL.h>
#include <string>
#include <cassert>

namespace rgp {
    struct TextureAsset {
        SDL_Texture* texture = nullptr;
        const std::string *path;
        float size = 0.0f;

        TextureAsset(SDL_Texture* texture, const std::string &path, const float size)
            : texture(texture), path(&path), size(size)
        {
            assert(texture != nullptr && "Texture is null.");
        }

        ~TextureAsset() {
            if (texture) SDL_DestroyTexture(texture);
            SDL_Log("Texture destroyed: %s", path->c_str());
        }

        // Forbid copying
        TextureAsset(const TextureAsset&)                               = delete;
        auto operator=(const TextureAsset&) -> TextureAsset&            = delete;

        // Allow moving
        TextureAsset(TextureAsset&& other) noexcept                     = default;
        auto operator=(TextureAsset&& other) noexcept -> TextureAsset&  = default;

    };
}