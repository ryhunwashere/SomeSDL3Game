#include "asset/asset_audio.h"

#include <stdexcept>
#include <string>
#include <SDL3/SDL_log.h>

rgp::Audio::Audio(const std::string& audioPath, const SDL_AudioDeviceID deviceId) {
    if (!SDL_LoadWAV(audioPath.c_str(), &m_fileSpec, &m_audioBuffer, &m_audioLength))
        throw std::runtime_error("WAV load error: " + std::string(SDL_GetError()));

    SDL_AudioSpec deviceSpec;
    if (!SDL_GetAudioDeviceFormat(deviceId, &deviceSpec, nullptr))
        throw std::runtime_error("Failed to get device format: " + std::string(SDL_GetError()));

    m_stream = SDL_CreateAudioStream(&m_fileSpec, &deviceSpec);
    if (!m_stream)
        throw std::runtime_error("Audio stream creation failure: " + std::string(SDL_GetError()));

    if (!SDL_BindAudioStream(deviceId, m_stream))
        throw std::runtime_error("Audio stream binding failure: " + std::string(SDL_GetError()));
}

rgp::Audio::~Audio() {
    cleanup();
}

void rgp::Audio::play() const {
    if (!m_stream || !m_audioBuffer) {
        SDL_Log("No audio to be played!");
        return;
    }

    SDL_ClearAudioStream(m_stream);
    SDL_PutAudioStreamData(m_stream, m_audioBuffer, m_audioLength);

    SDL_Log("Playing audio");
    SDL_ResumeAudioStreamDevice(m_stream);
}

void rgp::Audio::stop() const {
    if (m_stream)
        SDL_ClearAudioStream(m_stream);
}

void rgp::Audio::cleanup() {
    if (m_stream) {
        SDL_UnbindAudioStream(m_stream);
        SDL_DestroyAudioStream(m_stream);
        m_stream = nullptr;
    }
    if (m_audioBuffer) {
        SDL_free(m_audioBuffer);
        m_audioBuffer = nullptr;
    }
}
