#pragma once
#include <SDL3_ttf/SDL_ttf.h>

namespace rgp {
    struct FontAsset {
        TTF_Font* font = nullptr;
        float size = 0.0f;
    };
}