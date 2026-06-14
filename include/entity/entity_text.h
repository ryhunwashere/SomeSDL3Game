#pragma once
#include <string>
#include <SDL3_ttf/SDL_ttf.h>

#include "entity.h"
#include "engine/engine_text.h"
#include "enum/enum_fonttype.h"
#include "interface/interface_drawable.h"
#include "factory/factory_font.h"

namespace rgp {
    class TextEntity final : public Entity, public IDrawable {
    public:
        TextEntity(
            const TextEngine& engine,
            const FontFactory& factory,
            FontType fontType,
            const std::string& initialText);

        ~TextEntity() override;

        TextEntity(const TextEntity&) = delete;
        TextEntity& operator=(const TextEntity&) = delete;

        TextEntity(TextEntity&& other) noexcept : m_textPtr(other.m_textPtr) {
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

        void draw() override;
        void setText(const std::string& text) const;

    private:
        TTF_Text* m_textPtr;
    };
}
