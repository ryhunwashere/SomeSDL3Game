#pragma once

#include "game_context.h"
#include "interface/interface_drawable.h"
#include "interface/interface_fixed_updatable.h"
#include "interface/interface_updatable.h"

namespace rgp {
    class Scene : public IDrawable, public IUpdatable, public IFixedUpdatable {
    public:
        explicit Scene(GameContext& ctx) : m_ctx(ctx) {}
        ~Scene() override = default;

    protected:
        GameContext& m_ctx;
    };
}
