#pragma once
#include <SDL3/SDL_rect.h>
#include "type/type_vector2f.h"

namespace rgp {
    class Entity {
    public:
        virtual ~Entity() = 0;

        void setPosition(const Vector2F& pos)                { m_x = pos.x; m_y = pos.y; }
        void movePosition(const Vector2F& deltaPos)          { m_x += deltaPos.x; m_y += deltaPos.y; }
        void setSize(const float width, const float height)  { m_width = width; m_height = height; }
        void setSizeAndPosition(const SDL_FRect& rect) {
            m_width     = rect.w;
            m_height    = rect.h;
            m_x         = rect.x;
            m_y         = rect.y;
        }

        void moveX(const float deltaX)                      { m_x += deltaX; }
        void moveY(const float deltaY)                      { m_y += deltaY; }
        void setX(const float x)                            { m_x = x; }
        void setY(const float y)                            { m_y = y; }

        void increaseWidth(const float deltaWidth)          { m_width  += deltaWidth; }
        void increaseHeight(const float deltaHeight)        { m_height += deltaHeight; }
        void setWidth(const float width)                    { m_width  = width; }
        void setHeight(const float height)                  { m_height = height; }

        [[nodiscard]] auto getX()         const -> float      { return m_x; }
        [[nodiscard]] auto getY()         const -> float      { return m_y; }
        [[nodiscard]] auto getPosition()  const -> Vector2F   { return Vector2F{ m_x, m_y }; }
        [[nodiscard]] auto getWidth()     const -> float      { return m_width; }
        [[nodiscard]] auto getHeight()    const -> float      { return m_height; }
        [[nodiscard]] auto getFRect()     const -> SDL_FRect  { return SDL_FRect{ m_x, m_y, m_width, m_height }; }

        // Equals to width/2 + height/2
        [[nodiscard]] auto getCenter()    const -> float      { return m_width/2 + m_height/2; }

        // Equals to width/2
        [[nodiscard]] auto getTopMiddle() const -> float      { return m_width/2; }

    private:
        float m_x       = 0.0f;
        float m_y       = 0.0f;
        float m_width   = 0.0f;
        float m_height  = 0.0f;
    };

    inline Entity::~Entity() = default;
}