#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

namespace rgp {
    struct TextureInfo {
        SDL_Texture* texture = nullptr;
        std::string path;
        float size = 0.0f;
    };

    struct FontInfo {
        TTF_Font* font = nullptr;
        float size = 0.0f;
    };
}