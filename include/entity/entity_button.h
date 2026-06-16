#pragma once

#include <functional>
#include "entity.h"
#include "game_context.h"
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
            const std::function<void(ButtonEntity&)>& callback)
        :   m_renderer(ctx.getRendererEngine()),
            m_color(colorF),
            m_execCalllback(callback)
        {
            setSizeAndPosition(rect);
        }

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

            m_renderer.draw(m_color, &destRect);
        }

        void setColor(const ColorF& colorF) { m_color = colorF; }
        [[nodiscard]] auto getColor() const -> ColorF { return m_color; }

    private:
        RendererEngine& m_renderer;
        ColorF m_color;
        std::function<void(ButtonEntity&)> m_execCalllback;
    };
}
