#include <SDL3_ttf/SDL_ttf.h>
#include "asset/asset_font.h"

#include "except_sdl.h"

rgp::Font::Font(const std::string& fontPath, const float size) : m_fontPtr(TTF_OpenFont(fontPath.c_str(), size)) {
    if (!m_fontPtr)
        throw SDLException("Font failed to load");

    SDL_Log("Font loaded. Path: %s | Size: %f", fontPath.c_str(), size);
}

rgp::Font::~Font() {
    if (m_fontPtr) {
        TTF_CloseFont(m_fontPtr);
        m_fontPtr = nullptr;
        SDL_Log("Font destroyed");
    }
}