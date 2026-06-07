#pragma once
#include <string>
#include "entity.h"
#include "interface_drawable.h"
#include "interface_updatable.h"
#include "struct_asset_texture.h"

namespace rgp {
    class PlayerEntity : public Entity, public IDrawable, public IUpdatable {
    public:
        PlayerEntity(const std::string& texturePath);
        ~PlayerEntity() override;

        void draw() override;
        void update() override;
        auto getTextureAsset() -> const TextureAsset* { return m_textureAsset; };

    private:
        const TextureAsset* m_textureAsset;

        void updatePosition();
    };
};