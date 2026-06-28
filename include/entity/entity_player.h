#pragma once

#include "game_context.h"
#include "entity/entity.h"
#include "entity/entity_bullet.h"
#include "asset/asset_texture.h"
#include "asset/asset_track.h"
#include "manager/manager_bullet.h"

namespace rgp {
    class PlayerEntity final : public Entity {
    public:
        PlayerEntity(GameContext& ctx, BulletManager& bulletManager, TextureType textureType, AudioType audioType);
        ~PlayerEntity() override = default;

        void draw() const;
        void update(float dt);

        void setPosition(const Vector2F& pos) override {
            m_x             = pos.x;
            m_y             = pos.y;
            m_collider.x    = getCenter().x;
            m_collider.y    = getCenter().y;
        }

        void movePosition(const Vector2F &deltaPos) override {
            m_x           += deltaPos.x;
            m_y           += deltaPos.y;
            m_collider.x  += deltaPos.x;
            m_collider.y  += deltaPos.y;
        }

        void setCurrentLives(const uint8_t lives)                   { m_currentLives = lives; }

        [[nodiscard]] auto getCollider()        const -> Circle     { return m_collider; }
        [[nodiscard]] auto getGrazeCollider()   const -> Circle     { return m_grazeCollider; }
        [[nodiscard]] auto getCurrentLives()    const -> uint8_t    { return m_currentLives; }

    private:
        BulletManager& m_bulletMng;
        GameContext& m_ctx;
        BulletEntity m_bullet;
        Track m_shootTrack;
        Circle m_collider;
        Circle m_grazeCollider;
        Texture* m_texturePtr;
        uint64_t m_nextShootTime;
        uint8_t m_currentLives;
        bool m_isSlow = false;

        void updatePosition(float dt);
        void updateShooting(float dt);
    };
}
