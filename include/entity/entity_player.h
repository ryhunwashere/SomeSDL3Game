#pragma once
#include <memory>
#include "entity/entity.h"
#include "interface/interface_drawable.h"
#include "interface/interface_updatable.h"
#include "asset/asset_texture.h"
#include "manager/manager_texture.h"
#include "engine/engine_renderer.h"
#include "manager/manager_input.h"

namespace rgp {
    class PlayerEntity : public Entity, public IDrawable, public IUpdatable {
    public:
        PlayerEntity(
            RendererEngine& renderer,
            InputManager& input,
            TextureManager& textureManager,
            TextureType textureType
        );

        ~PlayerEntity() override = default;

        void draw() override;
        void update() override;

    private:
        const RendererEngine& m_renderer;
        const InputManager& m_input;
        std::shared_ptr<Texture> m_texture;

        void updatePosition();
    };
}