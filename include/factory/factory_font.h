#pragma once
#include <array>
#include <memory>

#include "asset/asset_font.h"
#include "enum/enum_fonttype.h"

namespace rgp {
    class FontFactory {
    public:
        explicit FontFactory();
        ~FontFactory() = default;

        auto getFont(FontType fontType) const -> Font*;

    private:
        std::array<std::unique_ptr<Font>, static_cast<size_t>(FontType::Count)> m_fontArray;
    };
}

