#pragma once
#include <SDL3/SDL.h>
#include <string>
#include <cassert>

namespace rgp {
    struct Texture {
        SDL_Texture* texture = nullptr;
        const std::string *path;
        float size = 0.0f;

        Texture(SDL_Texture* texture, const std::string &path, const float size)
            : texture(texture), path(&path), size(size)
        {
            assert(texture != nullptr && "Texture is null.");
        }

        ~Texture() {
            if (texture) SDL_DestroyTexture(texture);
            SDL_Log("Texture destroyed: %s", path->c_str());
        }

        // Forbid copying
        Texture(const Texture&)                               = delete;
        auto operator=(const Texture&) -> Texture&            = delete;

        // Allow moving
        Texture(Texture&& other) noexcept                     = default;
        auto operator=(Texture&& other) noexcept -> Texture&  = default;

    };
}