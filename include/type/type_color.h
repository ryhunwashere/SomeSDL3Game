#pragma once
#include <algorithm>
#include <SDL3/SDL_pixels.h>

namespace rgp {
    struct Color : SDL_Color {
        static constexpr uint8_t MIN_VAL = 0;
        static constexpr uint8_t MAX_VAL = 255;

        constexpr Color() : SDL_Color{.r = MIN_VAL, .g = MIN_VAL, .b = MIN_VAL, .a = MAX_VAL} {}

        template <typename T>
        requires std::convertible_to<T, uint8_t>
        constexpr Color(const T _r, const T _g, const T _b, const T _a) : SDL_Color() {
            r = std::clamp(static_cast<uint8_t>(_r), MIN_VAL, MAX_VAL);
            g = std::clamp(static_cast<uint8_t>(_g), MIN_VAL, MAX_VAL);
            b = std::clamp(static_cast<uint8_t>(_b), MIN_VAL, MAX_VAL);
            a = std::clamp(static_cast<uint8_t>(_a), MIN_VAL, MAX_VAL);
        }

        constexpr explicit Color(const SDL_Color& color) : SDL_Color() {
            r = std::clamp(color.r, MIN_VAL, MAX_VAL);
            g = std::clamp(color.g, MIN_VAL, MAX_VAL);
            b = std::clamp(color.b, MIN_VAL, MAX_VAL);
            a = std::clamp(color.a, MIN_VAL, MAX_VAL);
        }
    };
}