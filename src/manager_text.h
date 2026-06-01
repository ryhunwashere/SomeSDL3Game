#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

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

        // Factory methods to manage fonts
        TTF_Font* load_font(const std::string& path, float size);
        TTF_TextEngine* get_raw_engine() const { return m_engine; }

    private:
        TextManager() = default;
        TTF_TextEngine* m_engine = nullptr;
    };
}