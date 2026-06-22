#pragma once

#include "event.h"

namespace rgp::event {
    struct PlayerLivesChangeEvent final : Event {
        int8_t currentLives;
    };
}
