#include "asset/asset_audio.h"

#include <stdexcept>
#include <string>
#include <SDL3/SDL_log.h>

rgp::Audio::Audio(MIX_Mixer* mixer, const std::string& audioPath) {
    m_audioPtr = MIX_LoadAudio(mixer, audioPath.c_str(), false);
    if (!m_audioPtr)
        throw std::runtime_error("Audio loading failure: " + std::string(SDL_GetError()));

    SDL_Log("Audio loaded: %s", audioPath.c_str());
}

rgp::Audio::~Audio() {
    if (m_audioPtr) {
        MIX_DestroyAudio(m_audioPtr);
        SDL_Log("Audio destroyed");
    }
}
