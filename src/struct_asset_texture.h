#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

namespace rgp {
    struct TextureAsset {
        SDL_Texture* texture = nullptr;
        std::string path;
        float size = 0.0f;
    };
}