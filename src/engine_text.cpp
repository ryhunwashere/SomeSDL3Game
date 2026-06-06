#include <stdexcept>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "engine_text.h"
#include "engine_renderer.h"

constexpr float DEFAULT_INITIAL_SIZE = 24.0f;

rgp::TextEngine::TextEngine() {
    if (!TTF_Init())
        throwFontError("SDL TTF init error.");

    auto& renderer = rgp::RendererEngine::get();

    m_textEngine = TTF_CreateRendererTextEngine(renderer.getRenderer());

    if (!m_textEngine)
        throwFontError("Text engine init error.");

    SDL_Log("Text engine initialized.");
}

rgp::TextEngine::~TextEngine() {
    if (m_textEngine) {
        for (auto& [path, fontInfo] : m_fontMap) {
            TTF_CloseFont(fontInfo.font);
            SDL_Log("Unloaded font: %s", path.c_str());
        }

        TTF_DestroyRendererTextEngine(m_textEngine);
    }

    TTF_Quit();

    SDL_Log("Text engine unloaded.");
}

void rgp::TextEngine::throwFontError(const std::string& message) {
    throw std::runtime_error(message + " | SDL_Error: " + SDL_GetError());
}

auto rgp::TextEngine::loadFont(const std::string& path, float initialSize) -> TTF_Font* {
    auto& fontData = m_fontMap[path];

    if (fontData.font != nullptr) return fontData.font;

    fontData.font = TTF_OpenFont(path.c_str(), initialSize);
    if (!fontData.font) {
        m_fontMap.erase(path);
        throwFontError("Font failed to load. | Path: " + path);
    }

    fontData.size = initialSize;
    return fontData.font;
}

auto rgp::TextEngine::copyFont(const std::string& path) -> TTF_Font* {
    TTF_Font* existingFont = loadFont(path, DEFAULT_INITIAL_SIZE);

    TTF_Font* copiedFont = TTF_CopyFont(existingFont);
    if (!copiedFont)
        throwFontError("Failed to copy font. | Path: " + path);

    return copiedFont;
}