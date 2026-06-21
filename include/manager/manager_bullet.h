#pragma once
#include <array>

#include "game_context.h"
#include "entity/entity_bullet.h"

namespace rgp {
    constexpr size_t MAX_PLAYER_BULLET_COUNT = 128;

    class BulletManager {
    public:
        explicit BulletManager(GameContext& ctx);
        ~BulletManager();

        void update();
        void draw() const;
        void spawnBullet(const BulletEntity& bulletParams, Vector2F spawnPos);

        [[nodiscard]] auto getActiveBulletsCount() const -> size_t { return m_activeBullets; }

    private:
        RendererEngine& m_renderer;
        TimeManager& m_timeMng;
        std::array<BulletEntity, MAX_PLAYER_BULLET_COUNT> m_playerBulletPool;
        size_t m_activeBullets;
    };
}
