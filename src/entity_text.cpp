#include <stdexcept>
#include <string>
#include "entity_text.h"
#include "engine_text.h"

rgp::TextEntity::TextEntity(const std::string& fontPath) {
    m_font = rgp::TextEngine::get().copyFont(fontPath);
    m_text = TTF_CreateText(rgp::TextEngine::get().getTextEngine(), m_font, "", 1);

    if (!m_text)
        throw std::runtime_error(
            std::string("Text entity creation failed: ") + SDL_GetError()
        );
}

rgp::TextEntity::~TextEntity() {
    if (m_text) {
        SDL_Log("Deleting text: %s", m_text->text);
        TTF_DestroyText(m_text);
        m_text = nullptr;
    }

    m_font = nullptr;
}

void rgp::TextEntity::setText(const std::string& text) {
    if (m_text)
        TTF_SetTextString(m_text, text.c_str(), text.length());
}

void rgp::TextEntity::setColor(SDL_Color color) {
    if (m_text)
        TTF_SetTextColorFloat(
            m_text, color.r, color.g, color.b, color.a
        );
}

void rgp::TextEntity::draw() {
    if (!m_text) return;

    if (!TTF_DrawRendererText(m_text, getX(), getY()))
        throw std::runtime_error(
            std::string("Text drawing failed: ") + SDL_GetError()
        );
}
