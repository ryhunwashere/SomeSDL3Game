#pragma once
#include <cmath>

namespace rgp::util::math {
    static constexpr auto easeInOutCubed(const float x) -> float {
        return x < 0.5f ? 4.0f * x * x * x : 1.0f - ::powf(-2.0f * x + 2.0f, 3.0f) / 2.0f;
    }
}
