#pragma once

namespace entity
{
    class Entity
    {
    public:
        virtual ~Entity() = 0;

        virtual void setPosition(float x, float y) { m_x = x; m_y = y; }
        virtual void move(float deltaX, float deltaY) { m_x += deltaX; m_y += deltaY; }
        void moveX(float deltaX) { move(deltaX, 0.0f); }
        void moveY(float deltaY) { move(0.0f, deltaY); }

        float getX() const { return m_x; }
        float getY() const { return m_y; }

    protected:
        float m_x = 0.0f;
        float m_y = 0.0f;
    };

    inline Entity::~Entity() {}
}