#include "entity/entity_button.h"

rgp::ButtonEntity::ButtonEntity(
    GameContext& ctx,
    const SDL_FRect& rect,
    const ColorF& colorF,
    const std::string_view text) :
m_renderer(ctx.getRendererEngine()),
m_color(colorF),
m_text(ctx.getTextFactory().create(FontType::ZenMaruMedium32Left, text)) {
    setSizeAndPosition(rect);
    m_text->setPosition(Vector2F{ getX(), getY() });
    m_text->setColor(constant::color::BLACK_OPAQUE);
}

void rgp::ButtonEntity::draw() const {
    const SDL_FRect destRect{
        .x = getX(),
        .y = getY(),
        .w = getWidth(),
        .h = getHeight()
    };

    m_renderer.drawRect(m_color, &destRect);
    m_text->draw();
}