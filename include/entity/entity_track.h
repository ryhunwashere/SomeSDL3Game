#pragma once
#include <SDL3_mixer/SDL_mixer.h>

#include "manager/manager_audio.h"

namespace rgp {
    class TrackEntity {
    public:
        explicit TrackEntity(AudioManager& audioManager, AudioType type, bool isLooping);
        ~TrackEntity();

        TrackEntity(const TrackEntity&) = delete;
        TrackEntity& operator=(const TrackEntity&) = delete;

        void play() const;
        void pause() const;
        void stop(Sint64 fadeOutFrames = 0) const;
        void resume() const;

        [[nodiscard]] auto isPlaying() const -> bool;
        [[nodiscard]] auto isPaused() const -> bool;

        void setLooping(bool looping) const;

    private:
        MIX_Track* m_trackPtr;
        SDL_PropertiesID m_trackProps = 0;
    };
}
