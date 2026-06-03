#pragma once
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

namespace entity {
    class TextEntity {
    public:
        TextEntity() = default;
        ~TextEntity() { destroy(); }

        bool create(TTF_Font* font, const std::string& initial_text);

        void updateText(const std::string& text);

        void setColor(float r, float g, float b, float a);
        void setColor(float r, float g, float b);

        void setPosition(float x, float y);

        void move(float deltaX, float deltaY);
        void moveX(float deltaX);
        void moveY(float deltaY);

        void draw();

        void destroy();

        float getX() const
        {
            return m_x;
        }

        float getY() const
        {
            return m_y;
        }

    private:
        TTF_Text* m_text = nullptr;
        TTF_Font* m_font = nullptr;
        float m_x = 0.0f;
        float m_y = 0.0f;
        float m_size = 16.0f;
        char m_textBuffer[256]{};
    };
}