#pragma once

#include "game_context.h"
#include "entity/entity.h"
#include "manager/manager_bullet.h"

namespace rgp {
    class CharacterEntity : public Entity {
    public:
        static constexpr float COLLIDER_RADIUS	= 4.0f;

        CharacterEntity(GameContext &ctx, BulletManager &bulletManager, const TextureType textureType)
        :   m_bulletMng(bulletManager),
            m_ctx(ctx),
            m_collider{.x = getCenter().x, .y = getCenter().y, .r = COLLIDER_RADIUS},
            m_texturePtr(ctx.getTextureManager().getTexture(textureType))
        {
            setSize(m_texturePtr->getWidth(), m_texturePtr->getHeight());
        }

        ~CharacterEntity() override = default;

        virtual void draw() const       = 0;
        virtual void update(float dt)   = 0;

        void setPosition(const Vector2F& pos) override {
            m_x             = pos.x;
            m_y             = pos.y;
            m_collider.x    = getCenter().x;
            m_collider.y    = getCenter().y;
        }

        void movePosition(const Vector2F &deltaPos) override {
            m_x           += deltaPos.x;
            m_y           += deltaPos.y;
            m_collider.x  += deltaPos.x;
            m_collider.y  += deltaPos.y;
        }

        [[nodiscard]] auto getCollider() const -> Circle { return m_collider; }

    protected:
        BulletManager& m_bulletMng;
        GameContext& m_ctx;
        Circle m_collider;
        Texture* m_texturePtr;

        virtual void updatePosition(float dt) = 0;
        virtual void updateShooting(float dt) = 0;
    };
}
