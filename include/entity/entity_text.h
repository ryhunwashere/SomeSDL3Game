#pragma once
#include <string>
#include <SDL3_ttf/SDL_ttf.h>

#include "entity.h"
#include "interface/interface_drawable.h"

namespace rgp {
    class RendererEngine;
    struct Color;
    enum class FontType;
    class GameContext;

    class TextEntity final : public Entity, public IDrawable {
    public:
        TextEntity(GameContext& ctx, FontType fontType, std::string_view initialText);

        ~TextEntity() override;

        TextEntity(const TextEntity&) = delete;
        TextEntity& operator=(const TextEntity&) = delete;

        TextEntity(TextEntity&& other) noexcept : m_renderer(other.m_renderer), m_textPtr(other.m_textPtr) {
            other.m_textPtr = nullptr;
        }

        TextEntity& operator=(TextEntity&& other) noexcept {
            if (this != &other) {
                if (m_textPtr) TTF_DestroyText(m_textPtr);
                m_textPtr = other.m_textPtr;
                other.m_textPtr = nullptr;
            }
            return *this;
        }

        void draw(float alpha) override;
        void setText(std::string_view text) const;
        void setColor(const Color& color) const;

    private:
        RendererEngine& m_renderer;
        TTF_Text* m_textPtr;
    };
}
