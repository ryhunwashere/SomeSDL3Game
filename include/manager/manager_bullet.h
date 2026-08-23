#pragma once
#include <array>
#include <vector>

#include "entity/entity_bullet.h"
#include "interface/interface_drawable.h"
#include "interface/interface_fixed_updatable.h"

namespace rgp {
    struct Vector2F;
    class GameContext;

    static constexpr size_t MAX_PLAYER_BULLET_COUNT = 128;
    static constexpr size_t MAX_ENEMY_BULLET_COUNT  = 1024;

    template <size_t MaxBullets>
    struct BulletPool {
        std::array<BulletEntity, MaxBullets> memoryPool{};
        size_t activeCount = 0;
    };

    class BulletManager final : public IFixedUpdatable, public IDrawable {
    public:
        explicit BulletManager(GameContext& ctx);
        ~BulletManager() override = default;

        void fixedUpdate(float fixedDt) override;
        void draw(float alpha) override;

        void spawnPlayerBullet(const BulletEntity& bulletParams, Vector2F spawnPos);
        void spawnEnemyBullet(const BulletEntity& bulletParams, Vector2F spawnPos);

        void clearEnemyBullets();

    private:
        static constexpr float BULLET_ALPHA             = 0.8f;
        static constexpr int   VIEWPORT_OFFSIDE_MARGIN  = 200;

        BulletPool<MAX_PLAYER_BULLET_COUNT> m_playerPool{};
        BulletPool<MAX_ENEMY_BULLET_COUNT> m_enemyPool{};
        std::vector<Circle> m_circleColliderBuffer{};
        size_t m_activeBullets = 0;
        GameContext& m_ctx;

        template <size_t MaxBullets>
        void spawnBullet(BulletPool<MaxBullets>& pool, const BulletEntity& params, Vector2F spawnPos);

        template <size_t MaxBullets>
        void updateBullets(BulletPool<MaxBullets>& pool, float dt);

        template <size_t MaxBullets>
        void drawBullets(BulletPool<MaxBullets>& pool, float alpha);
    };
}
