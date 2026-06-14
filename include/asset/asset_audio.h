#pragma once
#include <string>
#include <SDL3/SDL_audio.h>

namespace rgp {
    class Audio {
    public:
        explicit Audio(const std::string& audioPath, SDL_AudioDeviceID deviceId);
        ~Audio();

        void play() const;
        void stop() const;

        Audio(const Audio&) = delete;
        Audio& operator=(const Audio&) = delete;

        Audio(Audio&& other) noexcept {
            *this = std::move(other);
        }

        Audio& operator=(Audio&& other) noexcept {
            if (this != &other) {
                cleanup();

                m_fileSpec          = other.m_fileSpec;
                m_audioBuffer       = other.m_audioBuffer;
                m_audioLength       = other.m_audioLength;
                m_stream            = other.m_stream;

                other.m_audioBuffer = nullptr;
                other.m_audioLength = 0;
                other.m_stream      = nullptr;
            }
            return *this;
        }

    private:
        SDL_AudioSpec m_fileSpec{};
        Uint8* m_audioBuffer        = nullptr;
        Uint32 m_audioLength        = 0;
        SDL_AudioStream* m_stream   = nullptr;

        void cleanup();
    };
}
