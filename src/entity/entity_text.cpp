#include "entity/entity_text.h"
#include "except_sdl.h"

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
        throw SDLException("Failed to create Text Entity");

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
        throw SDLException("Failed to draw text Entity");
}

void rgp::TextEntity::setText(const std::string& text) const {
    if (!TTF_SetTextString(m_textPtr, text.c_str(), text.length()))
        throw SDLException("Failed to set text Entity");
}

void rgp::TextEntity::setColor(const Color& color) const {
    if (!TTF_SetTextColor(m_textPtr, color.r, color.g, color.b, color.a))
        throw SDLException("Failed to set text color");
}
