#pragma once
#include "asset/asset_texture.h"
#include "entity/entity.h"

namespace rgp {
    enum class BulletBehaviour : uint8_t { Linear, Sine, Homing };

    struct BulletEntity final : Entity {
        Circle collider{};
        Texture* texturePtr;
        double angle;
        float timeAlive;
        float velocity;
        BulletBehaviour behaviour;
        bool isActive = false;

        BulletEntity(Texture* tex, const double angle, const float timeAlive, const float vel, const BulletBehaviour behaviour)
            : texturePtr(tex), angle(angle), timeAlive(timeAlive), velocity(vel), behaviour(behaviour) {
            setSize(texturePtr->getWidth(), texturePtr->getHeight());

            const float radius = texturePtr->getWidth() / 2.0f;
            collider = {
                .x = getCenter().x,
                .y = getCenter().y,
                .r = radius,
            };
        }

        BulletEntity() = default;

        void movePosition(const Vector2F &deltaPos) override {
            m_x         += deltaPos.x;
            m_y         += deltaPos.y;
            collider.x  += deltaPos.x;
            collider.y  += deltaPos.y;
        }

        void setPosition(const Vector2F& pos) override {
            m_x         = pos.x;
            m_y         = pos.y;
            collider.x  = getCenter().x;
            collider.y  = getCenter().y;
        }
    };
}
