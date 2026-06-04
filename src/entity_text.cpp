#include <stdexcept>
#include <string>
#include "entity_text.h"
#include "manager_font.h"

using namespace entity;

TextEntity::TextEntity(const std::string& fontPath, const std::string& initialText) {
    TTF_Font* copiedFont = manager::FontManager::get().copyFont(fontPath);
    TTF_TextEngine* textEngine = manager::FontManager::get().getTextEngine();

    m_font = copiedFont;

    m_text = TTF_CreateText(textEngine, copiedFont, initialText.c_str(), initialText.length());

    if (!m_text)
        throw std::runtime_error(
            std::string("Text entity creation failed: ") + SDL_GetError()
        );
}

TextEntity::~TextEntity() {
    if (m_text) {
        TTF_DestroyText(m_text);
        m_text = nullptr;
    }

    if (m_font) {
        TTF_CloseFont(m_font);
        m_font = nullptr;
    }
}

void TextEntity::updateText(const std::string& text) {
    if (m_text)
        TTF_SetTextString(m_text, text.c_str(), text.length());
}

void TextEntity::setColor(float r, float g, float b, float a) {
    if (m_text)
        TTF_SetTextColorFloat(m_text, r, g, b, a);
}

void TextEntity::setColor(float r, float g, float b) {
    setColor(r, g, b, SDL_ALPHA_OPAQUE_FLOAT);
}

void TextEntity::draw() {
    if (!m_text) return;

    if (!TTF_DrawRendererText(m_text, m_x, m_y))
        throw std::runtime_error(
            std::string("Text drawing failed: ") + SDL_GetError()
        );
}
