#pragma once

#include <functional>
#include "entity.h"
#include "game_context.h"
#include "constant/constant.h"
#include "interface/interface_drawable.h"
#include "interface/interface_updatable.h"
#include "type/type_color.h"

namespace rgp {
    class ButtonEntity final : public Entity, public IUpdatable, public IDrawable {
    public:
        ButtonEntity(
            GameContext& ctx,
            const SDL_FRect& rect,
            const ColorF& colorF,
            const std::string_view text,
            const std::function<void(ButtonEntity&)>& callback)
        :   m_renderer(ctx.getRendererEngine()),
            m_color(colorF),
            m_execCalllback(callback),
            m_text(ctx.getTextFactory().create(FontType::ZenMaruMedium32Left, text))
        {
            setSizeAndPosition(rect);
            m_text->setPosition(Vector2F{ getX(), getY() });
            m_text->setColor(constant::color::BLACK_OPAQUE);
        }

        ButtonEntity(
            GameContext& ctx,
            const SDL_FRect& rect,
            const ColorF& colorF,
            const std::string_view text)
        :   ButtonEntity(ctx, rect, colorF, text, nullptr) {}

        ButtonEntity(
            GameContext& ctx,
            const SDL_FRect& rect,
            const ColorF& colorF)
        :   ButtonEntity(ctx, rect, colorF, "", nullptr) {}

        void update() override {
            if (m_execCalllback)
                m_execCalllback(*this);
        }

        void draw() override {
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
        std::function<void(ButtonEntity&)> m_execCalllback;
        std::unique_ptr<TextEntity> m_text;
    };
}
