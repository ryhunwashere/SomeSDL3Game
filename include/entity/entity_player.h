#pragma once

#include "game_context.h"
#include "entity/entity.h"
#include "interface/interface_drawable.h"
#include "interface/interface_updatable.h"
#include "asset/asset_texture.h"

namespace rgp {
    class PlayerEntity final : public Entity, public IDrawable, public IUpdatable {
    public:
        PlayerEntity(GameContext& ctx, TextureType textureType);
        ~PlayerEntity() override = default;

        void draw() override;
        void update() override;

    private:
        const RendererEngine& m_renderer;
        const InputManager& m_input;
        Texture* m_texturePtr;

        void updatePosition();
    };
}