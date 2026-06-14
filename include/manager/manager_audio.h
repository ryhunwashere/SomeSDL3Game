#pragma once
#include <array>
#include <memory>
#include <SDL3/SDL_audio.h>

#include "asset/asset_audio.h"
#include "enum/enum_audio_type.h"

namespace rgp {
    class AudioManager {
    public:
        explicit AudioManager();
        ~AudioManager();

        auto getAudio(AudioType type) -> Audio*;
        void unloadAudio(AudioType type);

    private:
        const SDL_AudioDeviceID m_deviceId;
        const std::array<const char*, static_cast<size_t>(AudioType::Count)> m_audioPaths;
        std::array<std::unique_ptr<Audio>, static_cast<size_t>(AudioType::Count)> m_audioCache;
    };
}
