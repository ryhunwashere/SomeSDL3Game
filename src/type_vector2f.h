#pragma once
#include <SDL3/SDL_rect.h>

namespace rgp {
    struct Vector2F : SDL_FPoint {
        Vector2F() : SDL_FPoint() { x = 0.0f; y = 0.0f; }
        Vector2F(const float _x, const float _y) : SDL_FPoint() { x = _x; y = _y; }

        explicit Vector2F(const SDL_FPoint& point) : SDL_FPoint() { x = point.x; y = point.y; }

        auto operator+=(const Vector2F& o)       -> Vector2F& { x += o.x; y += o.y; return *this; }
        auto operator-=(const Vector2F& o)       -> Vector2F& { x -= o.x; y -= o.y; return *this; }
        auto operator*=(const float scalar)      -> Vector2F& { x *= scalar; y *= scalar; return *this; }
        auto operator/=(const float scalar)      -> Vector2F& { x /= scalar; y /= scalar; return *this; }

        auto operator+(const Vector2F& o)  const -> Vector2F { return Vector2F(*this) += o; }
        auto operator-(const Vector2F& o)  const -> Vector2F { return Vector2F(*this) -= o; }
        auto operator*(const float scalar) const -> Vector2F { return Vector2F(*this) *= scalar; }
        auto operator/(const float scalar) const -> Vector2F { return Vector2F(*this) /= scalar; }
    };
}