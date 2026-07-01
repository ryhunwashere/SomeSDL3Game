#pragma once
#include <SDL3/SDL_timer.h>

namespace rgp {
    class TimeManager {
    public:
        static constexpr float FIXED_DELTA_TIME = 1.0f / 120.0f;

        TimeManager() : m_lastTime(SDL_GetTicksNS()), m_lastFpsUpdate(m_lastTime) {}

        [[nodiscard]] static auto getElapsedGameTimeNS() -> uint64_t { return SDL_GetTicksNS(); }

        void updateDeltaTime();

        [[nodiscard]] auto consumeFixedTick() -> bool;
        [[nodiscard]] auto getInterpolationAlpha() const -> float { return m_accumulator / FIXED_DELTA_TIME; }
        [[nodiscard]] auto getDeltaTime() const     -> float { return m_deltaTime; }
        [[nodiscard]] auto getCurrentFps() const    -> float { return m_currentFps; }

    private:
        uint64_t m_lastTime      = 0;
        uint64_t m_lastFpsUpdate = 0;
        uint32_t m_frameCount    = 0;
        float m_deltaTime        = 0;
        float m_currentFps       = 0;

        float m_accumulator      = 0.0f;
        static constexpr float MAX_FRAME_TIME  = 0.25f;

        static constexpr uint64_t FPS_UPDATE_INTERVAL = 250'000'000;

        auto updateFps(uint64_t currentTime) -> void;
    };
}
