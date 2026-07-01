#pragma once
#include <memory>
#include <string_view>

#include "entity.h"
#include "interface/interface_drawable.h"
#include "type/type_color.h"

namespace rgp {
    class TextEntity;
    class RendererEngine;
    class GameContext;

    class ButtonEntity final : public Entity, public IDrawable {
    public:
        ButtonEntity(GameContext& ctx, const SDL_FRect& rect, const ColorF& colorF, std::string_view text);

        void draw(float alpha) override;

        void setColor(const ColorF& colorF)                 { m_color = colorF; }
        [[nodiscard]] auto getText() const -> TextEntity*   { return m_text.get(); }
        [[nodiscard]] auto getColor() const -> ColorF       { return m_color; }

    private:
        RendererEngine& m_renderer;
        ColorF m_color;
        std::unique_ptr<TextEntity> m_text;
    };
}
