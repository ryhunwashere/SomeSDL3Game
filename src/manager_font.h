#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <unordered_map>

namespace manager {
    class FontManager {
    public:
        static FontManager& get()
        {
            static FontManager instance;
            return instance;
        }

        bool init(SDL_Renderer* renderer);
        void shutdown();

        TTF_Font* loadFont(const std::string& path, const std::string& name, float size);

        TTF_Font* getFont(const std::string& name);

        TTF_TextEngine* getRawEngine() const { return m_engine; }

        FontManager(const FontManager&)             = delete;
        FontManager& operator=(const FontManager&)  = delete;
        FontManager(FontManager&&)                  = delete;
        FontManager& operator=(FontManager&&)       = delete;

    private:
        FontManager() = default;
        ~FontManager() = default;

        TTF_TextEngine* m_engine = nullptr;

        std::unordered_map<std::string, TTF_Font*> m_fontMap;
    };
}