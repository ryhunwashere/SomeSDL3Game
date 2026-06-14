#include "manager/manager_audio.h"

#include <stdexcept>
#include <string>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>

#include "constant/constant.h"

rgp::AudioManager::AudioManager() :
    m_deviceId([]() -> SDL_AudioDeviceID {
        if (!SDL_Init(SDL_INIT_AUDIO))
            throw std::runtime_error("Audio init failure: " + std::string(SDL_GetError()));

        const SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
        if (deviceId == 0)
            throw std::runtime_error("Open audio device failure: " + std::string(SDL_GetError()));

        return deviceId;
    }()),
    m_audioPaths([]() -> std::array<const char*, static_cast<size_t>(AudioType::Count)> {
        std::array<const char*, static_cast<size_t>(AudioType::Count)> arr{};

        arr[static_cast<size_t>(AudioType::PlayerShoot)] = constant::path::PLAYER_SHOOT_WAV_PATH;

        return arr;
    }())
{
    SDL_Log("Audio system & manager initialized");
}

rgp::AudioManager::~AudioManager() {
    if (m_deviceId != 0) {
        SDL_CloseAudioDevice(m_deviceId);
        SDL_Log("Audio device closed");
    }

    SDL_QuitSubSystem(SDL_INIT_AUDIO);
}

auto rgp::AudioManager::getAudio(AudioType type) -> Audio* {
    const size_t index = static_cast<size_t>(type);

    if (m_audioCache[index]) {
        SDL_Log("Loading audio from cache: %zu", index);
        return m_audioCache[index].get();
    }

    SDL_Log("Loading and caching audio: %zu", index);
    m_audioCache[index] = std::make_unique<Audio>(m_audioPaths[index], m_deviceId);
    return m_audioCache[index].get();
}

void rgp::AudioManager::unloadAudio(AudioType type) {
    if (const size_t index = static_cast<size_t>(type); m_audioCache[index]) {
        SDL_Log("Unloading audio: %d", static_cast<int>(type));
        m_audioCache[index].reset();
    }
}
