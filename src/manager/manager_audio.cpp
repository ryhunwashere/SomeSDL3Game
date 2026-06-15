#include "manager/manager_audio.h"

#include <stdexcept>
#include <string>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>

#include <SDL3_mixer/SDL_mixer.h>

#include "constant/constant.h"

rgp::AudioManager::AudioManager() :
    m_mixer([]() -> MIX_Mixer* {
        if (!MIX_Init())
            throw std::runtime_error("Failed to init SDL Mixer: " + std::string(SDL_GetError()));

        MIX_Mixer* mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
        if (!mixer)
            throw std::runtime_error("Failed to create mixer device: " + std::string(SDL_GetError()));

        return mixer;
    }()),
    m_audioPaths([]() -> std::array<const char*, static_cast<size_t>(AudioType::Count)> {
        std::array<const char*, static_cast<size_t>(AudioType::Count)> arr{};

        arr[static_cast<size_t>(AudioType::PlayerShoot)] = constant::path::PLAYER_SHOOT_WAV_PATH;
        arr[static_cast<size_t>(AudioType::MenuMusic)] = constant::path::MENU_MUSIC_MP3_PATH;

        return arr;
    }())
{}

rgp::AudioManager::~AudioManager() {
    for (auto& audio : m_audioCache) {
        if (audio) audio.reset();
    }

    SDL_Log("Destroying mixer...");
    MIX_Quit();
}

auto rgp::AudioManager::getAudio(AudioType type) -> Audio* {
    const auto index = static_cast<size_t>(type);

    if (m_audioCache[index]) {
        SDL_Log("Loading audio from cache: %zu", index);
        return m_audioCache[index].get();
    }

    SDL_Log("Loading and caching audio: %zu", index);
    m_audioCache[index] = std::make_unique<Audio>(m_mixer, m_audioPaths[index]);
    return m_audioCache[index].get();
}

void rgp::AudioManager::unloadAudio(AudioType type) {
    if (const auto index = static_cast<size_t>(type); m_audioCache[index]) {
        SDL_Log("Unloading audio: %zu", index);
        m_audioCache[index].reset();
    }
}
