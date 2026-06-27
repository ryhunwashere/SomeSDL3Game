#pragma once
#include <array>

#include "game_context.h"
#include "entity/entity_bullet.h"

namespace rgp {
    static constexpr size_t MAX_PLAYER_BULLET_COUNT = 128;
    static constexpr size_t MAX_ENEMY_BULLET_COUNT  = 1024;

    template <size_t MaxBullets>
    struct BulletPool {
        std::array<BulletEntity, MaxBullets> memoryPool{};
        std::array<size_t, MaxBullets> freeIndices = [] {
            std::array<size_t, MaxBullets> temp{};
            for (size_t i = 0; i < MaxBullets; ++i) temp[i] = i;
            return temp;
        }();
        size_t availableCount = MaxBullets;
    };

    class BulletManager {
    public:
        explicit BulletManager(GameContext& ctx);
        ~BulletManager() = default;

        void update();
        void draw();

        void spawnPlayerBullet(const BulletEntity& bulletParams, Vector2F spawnPos);
        void spawnEnemyBullet(const BulletEntity& bulletParams, Vector2F spawnPos);

    private:
        static constexpr float BULLET_ALPHA = 0.8f;
        BulletPool<MAX_PLAYER_BULLET_COUNT> m_playerPool{};
        BulletPool<MAX_ENEMY_BULLET_COUNT> m_enemyPool{};
        size_t m_activeBullets = 0;
        GameContext& m_ctx;

        template <size_t MaxBullets>
        void spawnBullet(BulletPool<MaxBullets>& pool, const BulletEntity& params, Vector2F spawnPos);

        template <size_t MaxBullets>
        void updateBullets(BulletPool<MaxBullets>& pool, float dt);

        template <size_t MaxBullets>
        void drawBullets(BulletPool<MaxBullets>& pool);
    };
}
