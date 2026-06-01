#pragma once
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

namespace entity {
    class TextEntity {
    public:
        TextEntity() = default;
        ~TextEntity() { destroy(); }

        bool create(TTF_Font* font, const std::string& initial_text);
        void update_text(const std::string& text);  // Change the text into the given string value.

        void set_color_float(float r, float g, float b, float a);
        void set_color_float(float r, float g, float b);

        /* Set the text position exactly into the provided x& y values.*/
        void set_position(float x, float y);

        /* Increment the text position by provided x& y values. */
        void move(float x, float y);

        /* Draw text into current m_pos_x & m_pos_y. */
        void draw();

        void destroy();

        float get_x() const
        {
            return m_pos_x;
        }

        float get_y() const
        {
            return m_pos_y;
        }

    private:
        TTF_Text* m_text_obj = nullptr;
        float m_pos_x = 0.0f;
        float m_pos_y = 0.0f;
        char m_text_buffer[256]{};
    };
}