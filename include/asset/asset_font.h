#pragma once
#include <string>
#include <SDL3_ttf/SDL_ttf.h>

namespace rgp {
    class Font {
    public:
        Font(const std::string& fontPath, float size);
        ~Font();

        Font(const Font&) = delete;
        Font& operator=(const Font&) = delete;

        [[nodiscard]] auto getFontPtr() const -> TTF_Font* { return m_fontPtr; }
        [[nodiscard]] auto getFontSize() const -> float { return m_fontSize; }

    private:
        TTF_Font* m_fontPtr;
        float m_fontSize;
    };
}
