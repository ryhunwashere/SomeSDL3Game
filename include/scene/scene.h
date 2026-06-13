#pragma once

#include "enum/enum_scenetype.h"

namespace rgp {
    class Scene {
    public:
        explicit Scene(const GameContext& ctx) : m_ctx(ctx) {}
        virtual ~Scene() = default;

        virtual auto update() -> SceneType = 0;
        virtual void draw() = 0;

    protected:
        const GameContext& m_ctx;
    };
}