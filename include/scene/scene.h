#pragma once

#include "enum/enum_scenetype.h"
#include "game_context.h"

namespace rgp {
    class Scene {
    public:
        explicit Scene(GameContext& ctx) : m_ctx(ctx) {}
        virtual ~Scene() = default;

        virtual auto update() -> SceneType = 0;
        virtual void draw() = 0;

    protected:
        GameContext& m_ctx;
    };
}