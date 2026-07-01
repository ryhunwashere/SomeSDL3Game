#pragma once
#include "asset/asset_texture.h"
#include "entity/entity.h"

namespace rgp {
    enum class BulletBehaviour : uint8_t { Linear, Sine, Homing };

    struct BulletEntity final : Entity {
        Circle collider{};
        BulletBehaviour behaviour{BulletBehaviour::Linear};
        Texture* texturePtr{nullptr};
        double angle{0.0};
        float timeAlive{0.0};
        float velocity{0.0};
        Vector2F currentPos{0.0f, 0.0f};
        Vector2F previousPos{0.0f, 0.0f};

        BulletEntity(Texture* tex, const double angle, const float timeAlive, const float vel, const BulletBehaviour behaviour)
            : behaviour(behaviour), texturePtr(tex), angle(angle), timeAlive(timeAlive), velocity(vel) {
            setSize(texturePtr->getWidth(), texturePtr->getHeight());

            const float radius = std::min(texturePtr->getWidth(), texturePtr->getHeight()) / 2.0f;
            const auto center = getCenter();

            collider = {
                .x = center.x,
                .y = center.y,
                .r = radius,
            };
        }

        BulletEntity() = default;

        void setPosition(const Vector2F pos) override {
            m_x             = pos.x;
            m_y             = pos.y;
            currentPos.x    = pos.x;
            currentPos.y    = pos.y;
            collider.x      = getCenter().x;
            collider.y      = getCenter().y;
        }

        void movePosition(const Vector2F deltaPos) override {
            m_x             += deltaPos.x;
            m_y             += deltaPos.y;
            currentPos.x    += deltaPos.x;
            currentPos.y    += deltaPos.y;
            collider.x      += deltaPos.x;
            collider.y      += deltaPos.y;
        }

        [[nodiscard]] auto getX() const -> float override { return currentPos.x; }
        [[nodiscard]] auto getY() const -> float override { return currentPos.y; }
    };
}
