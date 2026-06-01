#pragma once
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

namespace entity {
    class TextEntity {
    public:
        TextEntity() = default;
        ~TextEntity() { destroy(); }

        bool create(TTF_Font* font, const std::string& initial_text);
        void update_text(const std::string& text);

        void set_color_float(float r, float g, float b, float a);
        void set_color_float(float r, float g, float b);
        void set_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
        void set_color(Uint8 r, Uint8 g, Uint8 b);

        void draw(float x, float y);
        void destroy();

    private:
        TTF_Text* m_text_obj = nullptr;
    };
}