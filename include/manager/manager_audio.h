#pragma once
#include <array>
#include <memory>
#include <SDL3_mixer/SDL_mixer.h>

#include "asset/asset_audio.h"
#include "enum/enum_audio_type.h"

namespace rgp {
    class AudioManager {
    public:
        explicit AudioManager();
        ~AudioManager();

        auto getAudio(AudioType type) -> Audio*;
        void unloadAudio(AudioType type);

        [[nodiscard]] auto getMixer() const -> MIX_Mixer* { return m_mixer; }

    private:
        MIX_Mixer* m_mixer;
        const std::array<const char*, static_cast<size_t>(AudioType::Count)> m_audioPaths;
        std::array<std::unique_ptr<Audio>, static_cast<size_t>(AudioType::Count)> m_audioCache;
    };
}
