#pragma once
#include <string>
#include <memory>
#include "entity.h"
#include "interface_drawable.h"
#include "interface_updatable.h"
#include "struct_asset_texture.h"

namespace rgp {
    class PlayerEntity : public Entity, public IDrawable, public IUpdatable {
    public:
        PlayerEntity(const std::string& texturePath);
        ~PlayerEntity() override = default;

        void draw() override;
        void update() override;

    private:
        std::shared_ptr<const TextureAsset> m_textureAsset;
        void updatePosition();
    };
};