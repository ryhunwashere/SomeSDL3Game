#pragma once
#include <vector>
#include <memory>
#include "interface_drawable.h"
#include "interface_updatable.h"

namespace rgp {
    class Scene : public IDrawable, public IUpdatable {
    public:
        Scene()           = default;
        ~Scene() override = default;
    };
}