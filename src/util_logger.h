#pragma once
#include <string>
#include <SDL3/SDL_timer.h>

namespace rgp {
    class Util {
    public:
        static void logMessage(const std::string& message);

        /* Get total elapsed time in double since the first tick. */
        [[nodiscard]] static auto getElapsedGameTime() -> double {
            return static_cast<const double>(SDL_GetTicks());
        }
    };
}