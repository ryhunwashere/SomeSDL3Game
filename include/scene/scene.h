#pragma once

#include "game_context.h"

namespace rgp {
    class Scene {
    public:
        explicit Scene(GameContext& ctx) : m_ctx(ctx) {}
        virtual ~Scene() = default;

        virtual void update(float dt) = 0;
        virtual void draw()           = 0;

    protected:
        GameContext& m_ctx;
    };
}