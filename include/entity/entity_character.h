#pragma once

#include "game_context.h"
#include "entity/entity.h"
#include "interface/interface_drawable.h"
#include "interface/interface_fixed_updatable.h"
#include "manager/manager_bullet.h"

namespace rgp {
    class CharacterEntity : public Entity, public IFixedUpdatable, public IDrawable {
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

        void setPosition(const Vector2F pos) override {
            m_x             = pos.x;
            m_y             = pos.y;
            m_collider.x    = getCenter().x;
            m_collider.y    = getCenter().y;
        }

        void movePosition(const Vector2F deltaPos) override {
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
        float m_prevX = 0.0f;
        float m_prevY = 0.0f;

        virtual void updatePosition(float dt) = 0;
        virtual void updateShooting(float dt) = 0;
    };
}
