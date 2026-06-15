#include "entity/entity_track.h"
#include "asset/asset_audio.h"
#include "manager/manager_audio.h"
#include <cassert>

rgp::TrackEntity::TrackEntity(AudioManager& audioManager, const AudioType type, const bool isLooping) :
    m_trackPtr(MIX_CreateTrack(audioManager.getMixer())) {
    if (!m_trackPtr)
        throw std::runtime_error("Track creation failure: " + std::string(SDL_GetError()));

    if (!MIX_SetTrackAudio(m_trackPtr, audioManager.getAudio(type)->getAudioPtr()))
        throw std::runtime_error("Set track audio failure: " + std::string(SDL_GetError()));

    m_trackProps = SDL_CreateProperties();
    if (m_trackProps == 0)
        throw std::runtime_error("Props creation for track creation failure: " + std::string(SDL_GetError()));

    if (!SDL_SetNumberProperty(m_trackProps, MIX_PROP_PLAY_LOOPS_NUMBER, isLooping ? -1 : 0))
        throw std::runtime_error("Props setting for track failed: " + std::string(SDL_GetError()));
}

rgp::TrackEntity::~TrackEntity() {
    if (MIX_TrackPlaying(m_trackPtr) || MIX_TrackPaused(m_trackPtr))
        MIX_StopTrack(m_trackPtr, 0);

    MIX_DestroyTrack(m_trackPtr);
    SDL_DestroyProperties(m_trackProps);

    SDL_Log("Track destroyed");
}

void rgp::TrackEntity::play() const {
    if (!MIX_PlayTrack(m_trackPtr, m_trackProps))
        throw std::runtime_error("Failed to play track: " + std::string(SDL_GetError()));
}

void rgp::TrackEntity::pause() const {
    if (!MIX_PauseTrack(m_trackPtr))
        throw std::runtime_error("Failed to pause track: " + std::string(SDL_GetError()));
}

void rgp::TrackEntity::stop(const Sint64 fadeOutFrames) const {
    if (!MIX_StopTrack(m_trackPtr, fadeOutFrames))
        throw std::runtime_error("Failed to stop track: " + std::string(SDL_GetError()));
}

void rgp::TrackEntity::resume() const {
    if (!MIX_ResumeTrack(m_trackPtr))
        throw std::runtime_error("Failed to resume track: " + std::string(SDL_GetError()));
}

auto rgp::TrackEntity::isPaused() const -> bool {
    assert(m_trackPtr && "Track pointer is null!");
    return MIX_TrackPaused(m_trackPtr);
}

auto rgp::TrackEntity::isPlaying() const -> bool {
    assert(m_trackPtr && "Track pointer is null!");
    return MIX_TrackPlaying(m_trackPtr);
}

void rgp::TrackEntity::setLooping(const bool looping) const {
    if (!SDL_SetNumberProperty(m_trackProps, MIX_PROP_PLAY_LOOPS_NUMBER, looping ? -1 : 0))
        throw std::runtime_error("Props setting for track failed: " + std::string(SDL_GetError()));
}
