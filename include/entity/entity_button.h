#pragma once

#include "entity_text.h"
#include "game_context.h"
#include "entity/entity.h"
#include "type/type_color.h"

namespace rgp {
    class ButtonEntity final : public Entity {
    public:
        ButtonEntity(GameContext& ctx, const SDL_FRect& rect, const ColorF& colorF, std::string_view text);

        void draw() const;

        void setColor(const ColorF& colorF)                 { m_color = colorF; }
        [[nodiscard]] auto getText() const -> TextEntity*   { return m_text.get(); }
        [[nodiscard]] auto getColor() const -> ColorF       { return m_color; }

    private:
        RendererEngine& m_renderer;
        ColorF m_color;
        std::unique_ptr<TextEntity> m_text;
    };
}
