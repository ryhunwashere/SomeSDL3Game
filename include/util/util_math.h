#pragma once
#include <cmath>

namespace rgp::util::math {
    static constexpr auto easeInOutCubed(const float x) -> float {
        return x < 0.5f ? 4.0f * x * x * x : 1.0f - powf(-2.0f * x + 2.0f, 3.0f) / 2.0f;
    }

    static auto distanceSquared(const float x1, const float y1, const float x2, const float y2) -> float {
        const float deltaX = x2 - x1;
        const float deltaY = y2 - y1;

        return deltaX * deltaX + deltaY * deltaY;
    }
}
