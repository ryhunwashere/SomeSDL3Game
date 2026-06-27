#pragma once
#include "asset/asset_texture.h"
#include "entity/entity.h"

namespace rgp {
    enum class BulletBehaviour : uint8_t { Linear, Sine, Homing };

    struct BulletEntity final : Entity {
        Texture* texturePtr;
        double angle;
        float timeAlive;
        float velocity;
        BulletBehaviour behaviour;
        bool isActive = false;

        BulletEntity(Texture* tex, const double angle, const float timeAlive, const float vel, const BulletBehaviour behaviour)
            : texturePtr(tex), angle(angle), timeAlive(timeAlive), velocity(vel), behaviour(behaviour) {}

        BulletEntity() = default;
    };
}
