#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <unordered_map>

namespace manager {
    class FontManager {
    public:
        static auto get() -> FontManager&;

        auto loadFont(const std::string& path, float initialSize) -> TTF_Font*;

        auto copyFont(const std::string& path) -> TTF_Font*;

        [[nodiscard]] auto getTextEngine() const -> TTF_TextEngine* { return m_engine; }

        FontManager(const FontManager&)                     = delete;
        auto operator=(const FontManager&) -> FontManager&  = delete;
        FontManager(FontManager&&)                          = delete;
        auto operator=(FontManager&&) -> FontManager&       = delete;

    private:
        FontManager();
        ~FontManager();

        void throwFontError(const std::string& message);

        struct FontInfo {
            TTF_Font* font = nullptr;
            float size = 0.0f;
        };

        TTF_TextEngine* m_engine = nullptr;

        std::unordered_map<std::string, FontInfo> m_fontMap;
    };
}