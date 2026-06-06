#pragma once
#include <string>
#include "entity.h"
#include "interface_drawable.h"
#include "interface_updatable.h"
#include "struct_asset.h"

namespace rgp {
    class PlayerEntity : public Entity, public IDrawable, public IUpdatable {
    public:
        PlayerEntity(const std::string& texturePath);
        ~PlayerEntity() override;

        void draw() override;
        void update() override;
        auto getTextureInfo() -> const TextureInfo* { return m_textureInfo; };

    private:
        const TextureInfo* m_textureInfo;
    };
};