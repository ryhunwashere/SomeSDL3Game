#pragma once
#include <SDL3/SDL_timer.h>

namespace rgp {
    class TimeManager {
    public:
        TimeManager() : m_lastTime(SDL_GetTicksNS()), m_lastFpsUpdate(m_lastTime) {}

        [[nodiscard]] static auto getElapsedGameTimeNS() -> uint64_t { return SDL_GetTicksNS(); }

        void updateDeltaTime();

        [[nodiscard]] auto getDeltaTime() const     -> float { return m_deltaTime; }
        [[nodiscard]] auto getCurrentFps() const    -> float { return m_currentFps; }

    private:
        uint64_t m_lastTime      = 0;
        uint64_t m_lastFpsUpdate = 0;
        uint32_t m_frameCount    = 0;
        float m_deltaTime;
        float m_currentFps;
        static constexpr uint64_t FPS_UPDATE_INTERVAL = 250'000'000;

        auto updateFps(uint64_t currentTime) -> void;
    };
}
