#include "factory/factory_font.h"

#include <cassert>
#include <map>

rgp::FontFactory::FontFactory() {
    const std::map<FontType, std::pair<const std::string, float>> fontMap{
        { FontType::ZenMaruMedium32, {"asset/ZenMaruGothic-Medium.ttf", 32.0f } },
        { FontType::ZenMaruMedium24, {"asset/ZenMaruGothic-Medium.ttf", 24.0f } }
    };

    for (const auto& [fontType, fontConfig] : fontMap) {
        const auto index = static_cast<size_t>(fontType);
        m_fontArray[index] = std::make_unique<Font>(fontConfig.first, fontConfig.second);
    }
}

auto rgp::FontFactory::getFont(FontType fontType) const -> Font* {
    assert(fontType != FontType::Count && "'Count' is a forbidden FontType enum");
    const auto index = static_cast<size_t>(fontType);
    assert(index < static_cast<size_t>(FontType::Count) && "Out of bounds font access");

    return m_fontArray[index].get();
}
