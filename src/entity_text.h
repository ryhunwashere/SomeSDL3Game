#pragma once
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include "interface_drawable.h"
#include "entity.h"

namespace entity {
    class TextEntity : public Entity, public interface::IDrawable {
    public:
        TextEntity(const std::string& fontPath);
        ~TextEntity() override;

        void updateText(const std::string& text);
        void draw() override;

        void setColor(float r, float g, float b, float a);
        void setColor(float r, float g, float b);

        [[nodiscard]] auto getSize() const -> float { return m_size; }

    private:
        TTF_Text* m_text    = nullptr;
        TTF_Font* m_font    = nullptr;
        float m_size        = 16.0f;
    };
}