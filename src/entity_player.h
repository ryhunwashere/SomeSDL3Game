#pragma once
#include <string>
#include <memory>
#include "entity.h"
#include "interface_drawable.h"
#include "interface_updatable.h"
#include "asset_texture.h"
#include "engine_texture.h"
#include "engine_renderer.h"
#include "engine_input.h"

namespace rgp {
    class PlayerEntity : public Entity, public IDrawable, public IUpdatable {
    public:
        PlayerEntity(
            const std::string& texturePath, 
            RendererEngine& renderer, 
            TextureEngine& textureEngine, 
            InputEngine& inputEngine
        );

        ~PlayerEntity() override = default;

        void draw() override;
        void update() override;

    private:
        RendererEngine& m_renderer;
        TextureEngine& m_textureEngine;
        InputEngine& m_input;

        std::shared_ptr<const TextureAsset> m_textureAsset;
        void updatePosition();
    };
};