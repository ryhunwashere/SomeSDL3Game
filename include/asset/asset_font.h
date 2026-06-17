#pragma once
#include <string>
#include <SDL3_ttf/SDL_ttf.h>

namespace rgp {
    class Font {
    public:
        Font(std::string_view fontPath, float size, TTF_HorizontalAlignment align);
        ~Font();

        Font(const Font&) = delete;
        Font& operator=(const Font&) = delete;

        [[nodiscard]] auto getFontPtr() const -> TTF_Font* { return m_fontPtr; }

    private:
        TTF_Font* m_fontPtr;
    };
}
