#include "manager/manager_bullet.h"

#include <cmath>

#include "game_context.h"
#include "constant/constant.h"

rgp::BulletManager::BulletManager(GameContext& ctx) : m_ctx(ctx) {
    SDL_Log("Bullet manager loaded with O(1) Index Pools");
}

void rgp::BulletManager::fixedUpdate(const float fixedDt) {
    updateBullets(m_enemyPool, fixedDt);
    updateBullets(m_playerPool, fixedDt);
}

void rgp::BulletManager::draw(const float alpha) {
    drawBullets(m_enemyPool, alpha);
    drawBullets(m_playerPool, alpha);
}

void rgp::BulletManager::spawnPlayerBullet(const BulletEntity& bulletParams, const Vector2F spawnPos) {
    spawnBullet(m_playerPool, bulletParams, spawnPos);
}

void rgp::BulletManager::spawnEnemyBullet(const BulletEntity& bulletParams, const Vector2F spawnPos) {
    spawnBullet(m_enemyPool, bulletParams, spawnPos);
}

void rgp::BulletManager::clearEnemyBullets() {
    m_enemyPool.activeCount = 0;
}

template <size_t MaxBullets>
void rgp::BulletManager::spawnBullet(BulletPool<MaxBullets>& pool, const BulletEntity& params, Vector2F spawnPos) {
    if (pool.activeCount >= MaxBullets) [[unlikely]] return;

    auto& bullet = pool.memoryPool[pool.activeCount];

    bullet = params;
    bullet.currentPos  = spawnPos;
    bullet.previousPos = spawnPos;
    bullet.setPosition(spawnPos);
    ++pool.activeCount;
}

template <size_t MaxBullets>
void rgp::BulletManager::updateBullets(BulletPool<MaxBullets>& pool, const float dt) {
    for (size_t i = 0; i < pool.activeCount; ) {
        auto& bullet = pool.memoryPool[i];

        if (bullet.getX() < -VIEWPORT_OFFSIDE_MARGIN ||
            bullet.getX() > constant::dimension::VIEWPORT_WIDTH + VIEWPORT_OFFSIDE_MARGIN ||
            bullet.getY() < -VIEWPORT_OFFSIDE_MARGIN ||
            bullet.getY() > constant::dimension::VIEWPORT_HEIGHT + VIEWPORT_OFFSIDE_MARGIN) [[likely]]
        {
            --pool.activeCount;
            if (i < pool.activeCount)
                pool.memoryPool[i] = std::move(pool.memoryPool[pool.activeCount]);

            continue;
        }

        bullet.timeAlive -= dt;

        if (bullet.timeAlive <= 0.0f) {
            --pool.activeCount;
            if (i < pool.activeCount)
                pool.memoryPool[i] = std::move(pool.memoryPool[pool.activeCount]);

            continue;
        }

        const auto radians = static_cast<float>(bullet.angle * (std::numbers::pi / 180.0));

        bullet.previousPos = bullet.currentPos;

        bullet.movePosition({
            std::cos(radians) * bullet.velocity * dt,
            std::sin(radians) * bullet.velocity * dt
        });

        ++i;
    }
}

template <size_t MaxBullets>
void rgp::BulletManager::drawBullets(BulletPool<MaxBullets>& pool, const float alpha) {
    const auto& renderer = m_ctx.getRendererEngine();

    for (size_t i = 0; i < pool.activeCount; ++i) {
        const auto& bullet = pool.memoryPool[i];

        const float renderX = std::lerp(bullet.previousPos.x, bullet.currentPos.x, alpha);
        const float renderY = std::lerp(bullet.previousPos.y, bullet.currentPos.y, alpha);

        const SDL_FRect destRect{
            .x = renderX,
            .y = renderY,
            .w = bullet.getWidth(),
            .h = bullet.getHeight()
        };

        renderer.drawTexture(&destRect, bullet.texturePtr->getTexturePtr(), bullet.angle, BULLET_ALPHA);
    }

    m_circleColliderBuffer.clear();

    for (size_t i = 0; i < pool.activeCount; ++i) {
        const auto& bullet = pool.memoryPool[i];

        const float renderX = std::lerp(bullet.previousPos.x, bullet.currentPos.x, alpha);
        const float renderY = std::lerp(bullet.previousPos.y, bullet.currentPos.y, alpha);

        Circle lerpedCollider = bullet.collider;
        lerpedCollider.x = renderX + bullet.getWidth() * 0.5f;
        lerpedCollider.y = renderY + bullet.getHeight() * 0.5f;

        m_circleColliderBuffer.push_back(lerpedCollider);
    }

    renderer.drawCircleOutlinesBatch(m_circleColliderBuffer, Color{255, 0, 0, 100});
}