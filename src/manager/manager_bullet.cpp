#include "manager/manager_bullet.h"

#include <cmath>

rgp::BulletManager::BulletManager(GameContext& ctx) : m_ctx(ctx) {
    SDL_Log("Bullet manager loaded with O(1) Index Pools");
}

void rgp::BulletManager::update(const float dt) {
    updateBullets(m_enemyPool, dt);
    updateBullets(m_playerPool, dt);
}

void rgp::BulletManager::draw() {
    drawBullets(m_playerPool);
    drawBullets(m_enemyPool);
}

void rgp::BulletManager::spawnPlayerBullet(const BulletEntity& bulletParams, const Vector2F spawnPos) {
    spawnBullet(m_playerPool, bulletParams, spawnPos);
}

void rgp::BulletManager::spawnEnemyBullet(const BulletEntity& bulletParams, const Vector2F spawnPos) {
    spawnBullet(m_enemyPool, bulletParams, spawnPos);
}

template <size_t MaxBullets>
void rgp::BulletManager::spawnBullet(BulletPool<MaxBullets>& pool, const BulletEntity& params, Vector2F spawnPos) {
    if (pool.availableCount == 0) {
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Bullet pool exhausted! Max size: %zu", MaxBullets);
        return;
    }

    --pool.availableCount;
    size_t targetIndex = pool.freeIndices[pool.availableCount];

    auto& bullet = pool.memoryPool[targetIndex];
    bullet = params;
    bullet.setPosition(spawnPos);
    bullet.isActive = true;
}

template <size_t MaxBullets>
void rgp::BulletManager::updateBullets(BulletPool<MaxBullets>& pool, const float dt) {
    for (size_t i = 0; i < MaxBullets; ++i) {
        auto& bullet = pool.memoryPool[i];
        if (!bullet.isActive) continue;

        bullet.timeAlive -= dt;
        if (bullet.timeAlive <= 0.0f) {
            bullet.isActive = false;

            pool.freeIndices[pool.availableCount] = i;
            ++pool.availableCount;
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
void rgp::BulletManager::drawBullets(BulletPool<MaxBullets>& pool) {
    for (const auto& bullet : pool.memoryPool) {
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
