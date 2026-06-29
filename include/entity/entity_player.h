#pragma once

#include "entity/entity_character.h"
#include "asset/asset_track.h"

namespace rgp {
    class PlayerEntity final : public CharacterEntity {
    public:
        PlayerEntity(GameContext& ctx, BulletManager& bulletManager, TextureType textureType, AudioType audioType);
        ~PlayerEntity() override = default;

        void draw() const override;
        void update(float dt) override;

        void setCurrentLives(const uint8_t lives)                   { m_currentLives = lives; }

        [[nodiscard]] auto getGrazeCollider()   const -> Circle     { return m_grazeCollider; }
        [[nodiscard]] auto getCurrentLives()    const -> uint8_t    { return m_currentLives; }

    protected:
        void updatePosition(float dt) override;
        void updateShooting(float dt) override;

    private:
        BulletEntity m_bullet;
        Track m_shootTrack;
        Circle m_grazeCollider;
        uint64_t m_nextShootTime;
        uint8_t m_currentLives;
        bool m_isSlow = false;
    };
}
