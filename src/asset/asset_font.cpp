#include <SDL3_ttf/SDL_ttf.h>
#include "asset/asset_font.h"

#include "except_sdl.h"

rgp::Font::Font(const std::string_view fontPath, const float size, const TTF_HorizontalAlignment align)
    : m_fontPtr(TTF_OpenFont(fontPath.data(), size)) {
    if (!m_fontPtr)
        throw SDLException("Font failed to load");

    TTF_SetFontWrapAlignment(m_fontPtr, align);

    SDL_Log("Font loaded. Path: %s | Size: %f", fontPath.data(), size);
}

rgp::Font::~Font() {
    if (m_fontPtr) {
        TTF_CloseFont(m_fontPtr);
        m_fontPtr = nullptr;
        SDL_Log("Font destroyed");
    }
}