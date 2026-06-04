#pragma once
#include "common_vector2.h"

namespace entity {
    class Entity {
    public:
        virtual ~Entity() = 0;

        virtual void setPosition(common::Vector2 vec2) { 
            m_pos.x = vec2.x;
            m_pos.y = vec2.y;
        }

        virtual void move(common::Vector2 deltaVec2) { 
            m_pos.x += deltaVec2.x;
            m_pos.y += deltaVec2.y;
        }

        void moveX(float deltaX) { 
            move({ deltaX, 0.0f }); 
        }

        void moveY(float deltaY) { 
            move({ 0.0f, deltaY }); 
        }

        [[nodiscard]] auto getX() const -> float { return m_pos.x; }
        [[nodiscard]] auto getY() const -> float { return m_pos.y; }

    protected:
        common::Vector2 m_pos = { 0.0f, 0.0f };
    };

    inline Entity::~Entity() = default;
}