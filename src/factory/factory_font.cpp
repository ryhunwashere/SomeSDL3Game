#include <cassert>

#include "factory/factory_font.h"
#include "constant/constant.h"

rgp::FontFactory::FontFactory() : m_fontArray([] {
    constexpr auto ZEN_MARU_GOTHIC_MEDIUM = constant::path::ZEN_MARU_GOTHIC_MEDIUM_TTF_PATH;

    std::array<std::unique_ptr<Font>, static_cast<size_t>(FontType::Count)> arr{};

    arr[static_cast<size_t>(FontType::ZenMaruMedium24)] = std::make_unique<Font>(ZEN_MARU_GOTHIC_MEDIUM, 24.0f);
    arr[static_cast<size_t>(FontType::ZenMaruMedium32)] = std::make_unique<Font>(ZEN_MARU_GOTHIC_MEDIUM, 32.0f);

    return arr;
}()) {}

auto rgp::FontFactory::getFont(FontType fontType) const -> Font* {
    assert(fontType != FontType::Count && "'Count' is a forbidden FontType enum");

    const auto index = static_cast<size_t>(fontType);
    assert(index < static_cast<size_t>(FontType::Count) && "Out of bounds font access");

    return m_fontArray[index].get();
}
