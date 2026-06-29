#pragma once

#include "entity/entity_character.h"
#include "manager/manager_bullet.h"

namespace rgp {
    class EnemyEntity final : public CharacterEntity {
    public:
        EnemyEntity(GameContext &ctx, BulletManager &bulletManager, const TextureType textureType)
            : CharacterEntity(ctx, bulletManager, textureType) {}

        ~EnemyEntity() override = default;
    };
}
