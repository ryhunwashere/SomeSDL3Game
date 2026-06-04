#include <stdexcept>
#include <algorithm>
#include <cctype>
#include "engine_text.h"
#include "engine_renderer.h"

using namespace engine;

constexpr float DEFAULT_INITIAL_SIZE = 24.0f;

TextEngine::TextEngine() {
    if (!TTF_Init())
        throwFontError("SDL TTF init error.");

    auto& renderer = engine::RendererEngine::get();

    m_engine = TTF_CreateRendererTextEngine(renderer.getRenderer());

    if (!m_engine)
        throwFontError("Text engine init error.");
}

TextEngine::~TextEngine() {
    if (m_engine)
        TTF_DestroyRendererTextEngine(m_engine);

    TTF_Quit();
}

auto TextEngine::get() -> TextEngine& {
    static TextEngine instance;
    return instance;
}

void TextEngine::throwFontError(const std::string& message) {
    throw std::runtime_error(message + " | SDL_Error: " + SDL_GetError());
}

auto TextEngine::loadFont(const std::string& path, float initialSize) -> TTF_Font* {
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

auto TextEngine::copyFont(const std::string& path) -> TTF_Font* {
    TTF_Font* existingFont = loadFont(path, DEFAULT_INITIAL_SIZE);

    TTF_Font* copiedFont = TTF_CopyFont(existingFont);
    if (!copiedFont)
        throwFontError("Failed to copy font. | Path: " + path);

    return copiedFont;
}