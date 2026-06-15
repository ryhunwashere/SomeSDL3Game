#include <chrono>
#include "manager/manager_time.h"

void rgp::TimeManager::updateDeltaTime() {
    const auto currentTime = SDL_GetTicksNS();
    const auto deltaTimeNS = currentTime - m_lastTime;
    m_lastTime = currentTime;

    const std::chrono::nanoseconds duration(deltaTimeNS);
    m_deltaTime = std::chrono::duration<float>(duration).count();

    m_frameCount++;
    updateFps(currentTime);
}

void rgp::TimeManager::updateFps(const uint64_t currentTime) {
    if (const auto elapsedTime = currentTime - m_lastFpsUpdate; elapsedTime >= FPS_UPDATE_INTERVAL) {
        const auto duration = std::chrono::nanoseconds(elapsedTime);
        const auto elapsedSeconds = std::chrono::duration<float>(duration).count();

        m_currentFps = static_cast<float>(m_frameCount) / elapsedSeconds;

        m_frameCount = 0;
        m_lastFpsUpdate = currentTime;
    }
}