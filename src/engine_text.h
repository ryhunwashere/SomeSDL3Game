#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <unordered_map>
#include <vector>
#include "asset_font.h"
#include "engine_renderer.h"

namespace rgp {
    class TextEngine {
    public:
        TextEngine(RendererEngine& renderer);
        ~TextEngine();

        auto loadFont(const std::string& path, float initialSize) -> TTF_Font*;
        auto copyFont(const std::string& path) -> TTF_Font*;
        [[nodiscard]] auto getTextEngine() const -> TTF_TextEngine* { return m_textEngine; }

    private:
        void throwFontError(const std::string& message);

        TTF_TextEngine* m_textEngine = nullptr;
        std::unordered_map<std::string, FontAsset> m_fontMap;
    };
}