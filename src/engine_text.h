#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <unordered_map>
#include "abstract_singleton.h"

namespace engine {
    class TextEngine : public abstract::Singleton<TextEngine> {
        friend class abstract::Singleton<TextEngine>;

    public:
        auto loadFont(const std::string& path, float initialSize) -> TTF_Font*;
        auto copyFont(const std::string& path) -> TTF_Font*;
        [[nodiscard]] auto getTextEngine() const -> TTF_TextEngine* { return m_engine; }

    private:
        TextEngine();
        ~TextEngine();

        void throwFontError(const std::string& message);

        struct FontInfo {
            TTF_Font* font = nullptr;
            float size = 0.0f;
        };

        TTF_TextEngine* m_engine = nullptr;

        std::unordered_map<std::string, FontInfo> m_fontMap;
    };
}