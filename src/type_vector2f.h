#pragma once
#include <SDL3/SDL_rect.h>

namespace rgp {
    struct Vector2F : public SDL_FPoint {
        Vector2F() { x = 0.0f; y = 0.0f; }
        Vector2F(float _x, float _y) { x = _x; y = _y; }

        Vector2F(const SDL_FPoint& point) { x = point.x; y = point.y; }

        auto operator+=(const Vector2F& o)      -> Vector2F& { x += o.x; y += o.y; return *this; }
        auto operator-=(const Vector2F& o)      -> Vector2F& { x -= o.x; y -= o.y; return *this; }
        auto operator*=(float scalar)           -> Vector2F& { x *= scalar; y *= scalar; return *this; }
        auto operator/=(float scalar)           -> Vector2F& { x /= scalar; y /= scalar; return *this; }

        auto operator+(const Vector2F& o) const -> Vector2F { return Vector2F(*this) += o; }
        auto operator-(const Vector2F& o) const -> Vector2F { return Vector2F(*this) -= o; }
        auto operator*(float scalar)      const -> Vector2F { return Vector2F(*this) *= scalar; }
        auto operator/(float scalar)      const -> Vector2F { return Vector2F(*this) /= scalar; }
    };
};