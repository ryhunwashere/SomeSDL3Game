#pragma once
#include <string>
#include <SDL3/SDL_timer.h>

namespace rgp {
    class Util {
    public:
        static void logMessage(const std::string& message);

        /* Get total elapsed time in milliseconds (Uint64) since the first tick. */
        [[nodiscard]] static auto getElapsedGameTime() -> Uint64 { return SDL_GetTicks(); }
    };
}