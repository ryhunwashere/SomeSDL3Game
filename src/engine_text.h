#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <unordered_map>
#include <vector>
#include "abstract_singleton.h"
#include "struct_asset.h"
#include "entity_text.h"

namespace rgp {
    class TextEngine : public Singleton<TextEngine> {
        friend class Singleton<TextEngine>;

    public:
        auto loadFont(const std::string& path, float initialSize) -> TTF_Font*;
        auto copyFont(const std::string& path) -> TTF_Font*;
        [[nodiscard]] auto getTextEngine() const -> TTF_TextEngine* { return m_textEngine; }

    private:
        TextEngine();
        ~TextEngine();

        void throwFontError(const std::string& message);

        TTF_TextEngine* m_textEngine = nullptr;

        std::unordered_map<std::string, FontInfo> m_fontMap;
        std::vector<TextEntity> m_textEntities; // TODO: use fixed size array in later stage of dev
    };
}