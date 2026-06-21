#include "manager/manager_bullet.h"

#include <cmath>

constexpr float BULLET_ALPHA = 0.8f;

rgp::BulletManager::BulletManager(GameContext& ctx)
    : m_renderer(ctx.getRendererEngine()), m_timeMng(ctx.getTimeManager()), m_activeBullets(0) {
    std::array<BulletEntity, MAX_PLAYER_BULLET_COUNT> playerBulletPool;

    for (auto& bullet : playerBulletPool) bullet.isActive = false;

    m_playerBulletPool = std::move(playerBulletPool);

    SDL_Log("Bullet manager loaded");
}

rgp::BulletManager::~BulletManager() {
    SDL_Log("Unloading bullet manager...");
}

void rgp::BulletManager::update() {
    const float dt = m_timeMng.getDeltaTime();

    for (auto& bullet : m_playerBulletPool) {
        if (!bullet.isActive) continue;

        bullet.timeAlive -= dt;
        if (bullet.timeAlive <= 0.0f) {
            bullet.isActive = false;
            --m_activeBullets;
            continue;
        }

        const auto radians = static_cast<float>(bullet.angle * (std::numbers::pi / 180.0));

        Vector2F deltaPos{
            std::cos(radians) * bullet.velocity * dt,
            std::sin(radians) * bullet.velocity * dt
        };

        bullet.movePosition(deltaPos);
    }
}

void rgp::BulletManager::draw() const {
    for (const auto& bullet : m_playerBulletPool) {
        if (!bullet.isActive) continue;

        const SDL_FRect destRect{
            .x = bullet.getX(),
            .y = bullet.getY(),
            .w = bullet.getWidth(),
            .h = bullet.getHeight()
        };

        m_renderer.drawTexture(&destRect, bullet.texturePtr->getTexturePtr(), bullet.angle, BULLET_ALPHA);
    }
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
        ++m_activeBullets;
        break;
    }
}
