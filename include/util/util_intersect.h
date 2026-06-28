#pragma once
#include <SDL3/SDL_rect.h>

#include "util_math.h"
#include "type/type_circle.h"

namespace rgp::util::intersect {
    static bool hasIntersection(const Circle& circleA, const Circle& circleB) {
        const float distanceSquared = math::distanceSquared(circleA.x, circleA.y, circleB.x, circleB.y);
        const float radiusSquared   = (circleA.r + circleB.r) * (circleA.r + circleB.r);

        return distanceSquared < radiusSquared;
    }

    static auto hasIntersection(const SDL_FRect& rect, const Circle& circle) -> bool {
        const float closestX = std::clamp(circle.x, rect.x, rect.x + rect.w);
        const float closestY = std::clamp(circle.y, rect.y, rect.y + rect.h);

        const float distanceSquared = math::distanceSquared(circle.x, circle.y, closestX, closestY);
        const float radiusSquared   = circle.r * circle.r;

        return distanceSquared < radiusSquared;
    }
}
