#pragma once
#include <array>
#include <cmath>

#include "game_context.h"
#include "entity/entity_bullet.h"

namespace rgp {
    static constexpr size_t MAX_PLAYER_BULLET_COUNT = 128;
    static constexpr size_t MAX_ENEMY_BULLET_COUNT  = 1024;

    class BulletManager {
    public:
        explicit BulletManager(GameContext& ctx);
        ~BulletManager();

        void update();
        void draw();
        void spawnBullet(const BulletEntity& bulletParams, Vector2F spawnPos);

    private:
        static constexpr float BULLET_ALPHA = 0.8f;
        std::array<BulletEntity, MAX_ENEMY_BULLET_COUNT> m_enemyBulletPool;
        std::array<BulletEntity, MAX_PLAYER_BULLET_COUNT> m_playerBulletPool;
        GameContext& m_ctx;

        template <size_t MaxBullets>
        void updateBullets(std::array<BulletEntity, MaxBullets>& bulletPool, const float dt) {
            for (auto& bullet : bulletPool) {
                if (!bullet.isActive) continue;

                bullet.timeAlive -= dt;
                if (bullet.timeAlive <= 0.0f) {
                    bullet.isActive = false;
                    continue;
                }

                const auto radians = static_cast<float>(bullet.angle * (std::numbers::pi / 180.0));

                Vector2F deltaPos{
                    std::cos(radians) * bullet.velocity * dt,
                    std::sin(radians) * bullet.velocity * dt,
                };

                bullet.movePosition(deltaPos);
            }
        }

        template <size_t MaxBullets>
        void drawBullets(std::array<BulletEntity, MaxBullets>& bulletPool) {
            for (auto& bullet : bulletPool) {
                if (!bullet.isActive) continue;

                SDL_FRect destRect{
                    .x = bullet.getX(),
                    .y = bullet.getY(),
                    .w = bullet.getWidth(),
                    .h = bullet.getHeight()
                };

                m_ctx.getRendererEngine().drawTexture(&destRect, bullet.texturePtr->getTexturePtr(), bullet.angle, BULLET_ALPHA);
            }
        }
    };
}
