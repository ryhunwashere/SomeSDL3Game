#include <chrono>
#include "manager/manager_time.h"

void rgp::TimeManager::updateDeltaTime() {
    const auto currentTime = SDL_GetTicksNS();
    const auto deltaTimeNS = currentTime - m_lastTime;
    m_lastTime = currentTime;

    const auto duration = std::chrono::nanoseconds(deltaTimeNS);
    auto frameTime = std::chrono::duration<float>(duration).count();

    if (frameTime > MAX_FRAME_TIME) frameTime = MAX_FRAME_TIME;

    m_deltaTime = frameTime;
    m_accumulator += frameTime;

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

auto rgp::TimeManager::consumeFixedTick() -> bool {
    if (m_accumulator >= FIXED_DELTA_TIME) {
        m_accumulator -= FIXED_DELTA_TIME;
        return true;
    }

    return false;
}