#include "manager/manager_bullet.h"

#include <cmath>

rgp::BulletManager::BulletManager(GameContext& ctx)
:   m_ctx(ctx) {
    std::array<BulletEntity, MAX_PLAYER_BULLET_COUNT> playerBulletPool;
    std::array<BulletEntity, MAX_ENEMY_BULLET_COUNT> enemyBulletPool;

    for (auto& bullet : playerBulletPool) bullet.isActive = false;
    for (auto& bullet : enemyBulletPool)  bullet.isActive = false;

    m_playerBulletPool = std::move(playerBulletPool);
    m_enemyBulletPool  = std::move(enemyBulletPool);

    SDL_Log("Bullet manager loaded");
}

rgp::BulletManager::~BulletManager() {
    SDL_Log("Unloading bullet manager...");
}

void rgp::BulletManager::update() {
    const float dt = m_ctx.getTimeManager().getDeltaTime();

    updateBullets<MAX_ENEMY_BULLET_COUNT>(m_enemyBulletPool, dt);
    updateBullets<MAX_PLAYER_BULLET_COUNT>(m_playerBulletPool, dt);
}

void rgp::BulletManager::draw() {
    drawBullets<MAX_PLAYER_BULLET_COUNT>(m_playerBulletPool);
    drawBullets<MAX_ENEMY_BULLET_COUNT>(m_enemyBulletPool);
}

void rgp::BulletManager::spawnBullet(const BulletEntity &bulletParams, const Vector2F spawnPos) {
    for (auto& bullet : m_playerBulletPool) {
        if (bullet.isActive) continue;

        bullet.setPosition(spawnPos);
        bullet.setSize(bulletParams.getWidth(), bulletParams.getHeight());

        bullet.texturePtr   = bulletParams.texturePtr;
        bullet.angle        = bulletParams.angle;
        bullet.timeAlive    = bulletParams.timeAlive;
        bullet.velocity     = bulletParams.velocity;
        bullet.behaviour    = bulletParams.behaviour;
        bullet.isActive     = true;
        break;
    }
}
