#pragma once

#include "game_context.h"
#include "entity/entity.h"
#include "asset/asset_texture.h"
#include "asset/asset_track.h"
#include "manager/manager_bullet.h"

namespace rgp {
    class PlayerEntity final : public Entity {
    public:
        PlayerEntity(GameContext& ctx, BulletManager& bulletManager, TextureType textureType, AudioType audioType);
        ~PlayerEntity() override = default;

        void draw() const;
        void update();

    private:
        BulletEntity m_bullet;
        GameContext& m_ctx;
        BulletManager& m_bulletMng;
        Texture* m_texturePtr;
        std::unique_ptr<Track> m_shootTrack;
        uint64_t m_nextShootTime;
        int8_t m_currentLives;

        void updatePosition();
        void updateShooting();
    };
}
