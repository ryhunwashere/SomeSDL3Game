#include "entity/entity_text.h"

rgp::TextEntity::TextEntity(
    const TextEngine& engine,
    const FontFactory& factory,
    const FontType fontType,
    const std::string& initialText)
:
    m_textPtr(TTF_CreateText(
        engine.getEnginePtr(),
        factory.getFont(fontType)->getFontPtr(),
        initialText.c_str(),
        initialText.length()))
{
    if (!m_textPtr)
        throw std::runtime_error("Failed to create Text Entity: " + std::string(SDL_GetError()));

    SDL_Log("Text Entity created. Text: %s", initialText.c_str());
}

rgp::TextEntity::~TextEntity() {
    if (m_textPtr) {
        TTF_DestroyText(m_textPtr);
        m_textPtr = nullptr;
        SDL_Log("Text Entity destroyed.");
    }
}

void rgp::TextEntity::draw() {
    if (!TTF_DrawRendererText(m_textPtr, getX(), getY()))
        throw std::runtime_error("Failed to draw Text Entity: " + std::string(SDL_GetError()));
}

void rgp::TextEntity::setText(const std::string& text) const {
    if (!TTF_SetTextString(m_textPtr, text.c_str(), text.length()))
        throw std::runtime_error("Failed to set Text Entity: " + std::string(SDL_GetError()));
}