#include <stdexcept>
#include <algorithm>
#include <cctype>
#include "manager_font.h"
#include "engine_renderer.h"

using namespace manager;

constexpr float DEFAULT_INITIAL_SIZE = 24.0f;

FontManager::FontManager() {
    if (!TTF_Init())
        throwFontError("SDL TTF init error.");

    auto& renderer = engine::RendererEngine::get();

    m_engine = TTF_CreateRendererTextEngine(renderer.getRenderer());

    if (!m_engine)
        throwFontError("Text engine init error.");
}

FontManager::~FontManager() {
    if (m_engine)
        TTF_DestroyRendererTextEngine(m_engine);

    TTF_Quit();
}

FontManager& FontManager::get() {
    static FontManager instance;
    return instance;
}

void FontManager::throwFontError(const std::string& message) {
    throw std::runtime_error(message + " | SDL_Error: " + SDL_GetError());
}

TTF_Font* FontManager::loadFont(const std::string& path, float initialSize) {
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

TTF_Font* FontManager::copyFont(const std::string& path) {
    TTF_Font* existingFont = loadFont(path, DEFAULT_INITIAL_SIZE);

    TTF_Font* copiedFont = TTF_CopyFont(existingFont);
    if (!copiedFont)
        throwFontError("Failed to copy font. | Path: " + path);

    return copiedFont;
}