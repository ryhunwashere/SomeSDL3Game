#pragma once
#include <SDL3/SDL.h>
#include "type_vector2f.h"

namespace rgp {
    class Entity {
    public:
        virtual ~Entity() = 0;

        void setPosition(const Vector2F pos)                 { m_pos = pos; }
        void movePosition(const Vector2F deltaPos)           { m_pos += deltaPos; }

        void moveX(const float deltaX)                       { m_pos.x += deltaX; }
        void moveY(const float deltaY)                       { m_pos.y += deltaY; }
        void setX(const float x)                             { m_pos.x = x; }
        void setY(const float y)                             { m_pos.y = y; }

        [[nodiscard]] auto getX()        const -> float     { return m_pos.x; }
        [[nodiscard]] auto getY()        const -> float     { return m_pos.y; }
        [[nodiscard]] auto getPosition() const -> Vector2F  { return m_pos; }

    private:
        Vector2F m_pos = { 0.0f, 0.0f };
    };

    inline Entity::~Entity() = default;
}