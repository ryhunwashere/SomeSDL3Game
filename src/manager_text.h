#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <unordered_map>

namespace manager {
    class TextManager {
    public:
        static TextManager& get() 
        {
            static TextManager instance;
            return instance;
        }

        bool initialize(SDL_Renderer* renderer);
        void shutdown();

        TTF_Font* load_font(const std::string& path, const std::string& key, float size);
        TTF_Font* get_font(const std::string& key);

        TTF_TextEngine* get_raw_engine() const { return m_engine; }

        // Prevent copying and moving
        TextManager(const TextManager&)             = delete;
        TextManager& operator=(const TextManager&)  = delete;
        TextManager(TextManager&&)                  = delete;
        TextManager& operator=(TextManager&&)       = delete;

    private:
        TextManager() = default;
        TTF_TextEngine* m_engine = nullptr;

        static std::unordered_map<std::string, TTF_Font*>& get_font_map()
        {
            static std::unordered_map<std::string, TTF_Font*> instance;
            return instance;
        }
    };
}