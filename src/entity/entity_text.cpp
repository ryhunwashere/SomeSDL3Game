#include "entity/entity_text.h"
#include "except_sdl.h"

rgp::TextEntity::TextEntity(
    GameContext& ctx,
    const FontType fontType,
    const std::string_view initialText)
:   m_renderer(ctx.getRendererEngine()),
    m_textPtr(
    TTF_CreateText(
        ctx.getTextEngine().getEnginePtr(),
        ctx.getFontFactory().getFont(fontType)->getFontPtr(),
        initialText.data(),
        initialText.length()))
{
    if (!m_textPtr)
        throw SDLException("Failed to create Text Entity");

    SDL_Log("Text Entity created. Text: %s", initialText.data());
}

rgp::TextEntity::~TextEntity() {
    if (m_textPtr) {
        TTF_DestroyText(m_textPtr);
        m_textPtr = nullptr;
        SDL_Log("Text Entity destroyed.");
    }
}

void rgp::TextEntity::draw() {
    constexpr float OVERSAMPLE_SCALE = 2.0f;
    constexpr float INVERSE_SCALE = 1.0f / OVERSAMPLE_SCALE;

    const float scaledX = getX() * OVERSAMPLE_SCALE;
    const float scaledY = getY() * OVERSAMPLE_SCALE;

    SDL_SetRenderScale(m_renderer.getRenderer(), INVERSE_SCALE, INVERSE_SCALE);

    const bool success = TTF_DrawRendererText(m_textPtr, scaledX, scaledY);

    SDL_SetRenderScale(m_renderer.getRenderer(), 1.0f, 1.0f);

    if (!success)
        throw SDLException("Failed to draw text Entity");
}

void rgp::TextEntity::setText(const std::string_view text) const {
    if (!TTF_SetTextString(m_textPtr, text.data(), text.length()))
        throw SDLException("Failed to set text Entity");
}

void rgp::TextEntity::setColor(const Color& color) const {
    if (!TTF_SetTextColor(m_textPtr, color.r, color.g, color.b, color.a))
        throw SDLException("Failed to set text color");
}
