#pragma once

#include "event.h"

namespace rgp::event {
    struct PauseStateChangeEvent final : Event {
        bool isPaused;
    };
}
