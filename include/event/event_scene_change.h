#pragma once
#include "event.h"
#include "enum/enum_scenetype.h"

namespace rgp::event {
    struct SceneChangeEvent final : Event {
        SceneType scene;
    };
}
