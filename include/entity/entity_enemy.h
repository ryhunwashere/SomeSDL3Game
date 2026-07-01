#pragma once

#include "entity/entity_character.h"
#include "manager/manager_bullet.h"

namespace rgp {
    class EnemyEntity : public CharacterEntity {
    public:
        EnemyEntity(GameContext &ctx, BulletManager &bulletManager, TextureType textureType);
        ~EnemyEntity() override = default;

        void fixedUpdate(float fixedDt) override;
        void draw(float alpha) override;
    };
}
