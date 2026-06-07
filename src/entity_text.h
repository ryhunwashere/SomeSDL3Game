#pragma once
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include "interface_drawable.h"
#include "entity.h"

namespace rgp {
    class TextEntity : public Entity, public IDrawable {
    public:
        TextEntity(const std::string& fontPath);
        ~TextEntity() override;

        void setText(const std::string& text);
        void draw() override;
        void setColor(SDL_Color color);
        [[nodiscard]] auto getSize() const -> float { return m_size; }

    private:
        TTF_Font* m_font;
        TTF_Text* m_text;
        float m_size = 16.0f;
    };
}