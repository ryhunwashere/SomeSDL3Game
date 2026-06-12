#include <SDL3_ttf/SDL_ttf.h>
#include <stdexcept>
#include "asset/asset_font.h"

rgp::Font::Font(const std::string& fontPath, const float size) : m_fontPtr(TTF_OpenFont(fontPath.c_str(), size)) {
    if (!m_fontPtr)
        throw std::runtime_error("Font failed to load: " + std::string(SDL_GetError()));

    SDL_Log("Font loaded. Path: %s | Size: %f", fontPath.c_str(), size);
}

rgp::Font::~Font() {
    if (m_fontPtr) {
        TTF_CloseFont(m_fontPtr);
        m_fontPtr = nullptr;
        SDL_Log("Font destroyed");
    }
}