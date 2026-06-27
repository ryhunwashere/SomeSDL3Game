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

    private:
        BulletManager& m_bulletMng;
        GameContext& m_ctx;
        BulletEntity m_bullet;
        Track m_shootTrack;
        SDL_FRect m_hitbox;
        Texture* m_texturePtr;
        uint64_t m_nextShootTime;
        uint8_t m_currentLives;
        bool m_isSlow = false;

        void updatePosition(float dt);
        void updateShooting(float dt);
    };
}
