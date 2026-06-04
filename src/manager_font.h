#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <unordered_map>

namespace manager 
{
    class FontManager 
    {
    public:
        static FontManager& get();

        TTF_Font* loadFont(const std::string& path, float initialSize);

        TTF_Font* copyFont(const std::string& path);

        TTF_TextEngine* getTextEngine() const { return m_engine; }

        FontManager(const FontManager&)             = delete;
        FontManager& operator=(const FontManager&)  = delete;
        FontManager(FontManager&&)                  = delete;
        FontManager& operator=(FontManager&&)       = delete;

    private:
        FontManager();
        ~FontManager();

        void throwFontError(const std::string& message);

        struct FontInfo
        {
            TTF_Font* font = nullptr;
            float size = 0.0f;
        };

        TTF_TextEngine* m_engine = nullptr;

        std::unordered_map<std::string, FontInfo> m_fontMap;
    };
}