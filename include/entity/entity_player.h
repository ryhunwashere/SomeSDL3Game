#pragma once
#include <string>
#include <memory>
#include "entity/entity.h"
#include "interface/interface_drawable.h"
#include "interface/interface_updatable.h"
#include "asset/asset_texture.h"
#include "engine/engine_texture.h"
#include "engine/engine_renderer.h"
#include "engine/engine_input.h"

namespace rgp {
    class PlayerEntity : public Entity, public IDrawable, public IUpdatable {
    public:
        PlayerEntity(
            const std::string& texturePath, 
            const RendererEngine& renderer,
            TextureEngine& textureEngine,
            const InputEngine& inputEngine
        );

        ~PlayerEntity() override = default;

        void draw() override;
        void update() override;

    private:
        const RendererEngine& m_renderer;
        TextureEngine& m_textureEngine;
        const InputEngine& m_input;

        std::shared_ptr<const Texture> m_textureAsset;
        void updatePosition();
    };
}