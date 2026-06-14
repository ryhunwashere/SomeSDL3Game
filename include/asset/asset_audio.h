#pragma once
#include <string>
#include <SDL3_mixer/SDL_mixer.h>

namespace rgp {
    class Audio {
    public:
        explicit Audio(MIX_Mixer* mixer, const std::string& audioPath);
        ~Audio();

        [[nodiscard]] auto getAudioPtr() const -> MIX_Audio* { return m_audioPtr; }

        Audio(const Audio&) = delete;
        Audio& operator=(const Audio&) = delete;

    private:
        MIX_Audio* m_audioPtr;
    };
}
