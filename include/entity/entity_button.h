#pragma once

#include "game_context.h"
#include "entity/entity.h"
#include "constant/constant.h"
#include "type/type_color.h"

namespace rgp {
    class ButtonEntity final : public Entity {
    public:
        ButtonEntity(
            GameContext& ctx,
            const SDL_FRect& rect,
            const ColorF& colorF,
            const std::string_view text)
        :   m_renderer(ctx.getRendererEngine()),
            m_color(colorF),
            m_text(ctx.getTextFactory().create(FontType::ZenMaruMedium32Left, text))
        {
            setSizeAndPosition(rect);
            m_text->setPosition(Vector2F{ getX(), getY() });
            m_text->setColor(constant::color::BLACK_OPAQUE);
        }

        void draw() const {
            const SDL_FRect destRect{
                .x = getX(),
                .y = getY(),
                .w = getWidth(),
                .h = getHeight()
            };

            m_renderer.drawRect(m_color, &destRect);
            m_text->draw();
        }

        void setColor(const ColorF& colorF)                 { m_color = colorF; }
        [[nodiscard]] auto getText() const -> TextEntity*   { return m_text.get(); }
        [[nodiscard]] auto getColor() const -> ColorF       { return m_color; }

    private:
        RendererEngine& m_renderer;
        ColorF m_color;
        std::unique_ptr<TextEntity> m_text;
    };
}
