#include "asset/asset_track.h"
#include "asset/asset_audio.h"
#include "manager/manager_audio.h"
#include <cassert>

#include "except_sdl.h"

rgp::Track::Track(AudioManager& audioManager, const AudioType type, const bool isLooping) :
    m_trackPtr(MIX_CreateTrack(audioManager.getMixer())) {
    if (!m_trackPtr)
        throw SDLException("Track creation failure: " );

    if (!MIX_SetTrackAudio(m_trackPtr, audioManager.getAudio(type)->getAudioPtr()))
        throw SDLException("Set track audio failure: " );

    m_trackProps = SDL_CreateProperties();
    if (m_trackProps == 0)
        throw SDLException("Props creation for track creation failure: " );

    if (!SDL_SetNumberProperty(m_trackProps, MIX_PROP_PLAY_LOOPS_NUMBER, isLooping ? -1 : 0))
        throw SDLException("Props setting for track failed: " );
}

rgp::Track::~Track() {
    if (MIX_TrackPlaying(m_trackPtr) || MIX_TrackPaused(m_trackPtr))
        MIX_StopTrack(m_trackPtr, 0);

    MIX_DestroyTrack(m_trackPtr);
    SDL_DestroyProperties(m_trackProps);

    SDL_Log("Track destroyed");
}

void rgp::Track::play() const {
    if (!MIX_PlayTrack(m_trackPtr, m_trackProps))
        throw SDLException("Failed to play track");
}

void rgp::Track::pause() const {
    if (!MIX_PauseTrack(m_trackPtr))
        throw SDLException("Failed to pause track");
}

void rgp::Track::stop(const Sint64 fadeOutFrames) const {
    if (!MIX_StopTrack(m_trackPtr, fadeOutFrames))
        throw SDLException("Failed to stop track");
}

void rgp::Track::resume() const {
    if (!MIX_ResumeTrack(m_trackPtr))
        throw SDLException("Failed to resume track");
}

auto rgp::Track::isPaused() const -> bool {
    assert(m_trackPtr && "Track pointer is null!");
    return MIX_TrackPaused(m_trackPtr);
}

auto rgp::Track::isPlaying() const -> bool {
    assert(m_trackPtr && "Track pointer is null!");
    return MIX_TrackPlaying(m_trackPtr);
}

void rgp::Track::setLooping(const bool looping) const {
    if (!SDL_SetNumberProperty(m_trackProps, MIX_PROP_PLAY_LOOPS_NUMBER, looping ? -1 : 0))
        throw SDLException("Props setting for track failed");
}
