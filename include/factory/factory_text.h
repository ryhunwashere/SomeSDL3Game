#pragma once

#include <memory>
#include "engine/engine_text.h"
#include "entity/entity_text.h"
#include "enum/enum_fonttype.h"

namespace rgp {
    class TextFactory {
    public:
        TextFactory(const TextEngine& engine, const FontFactory& factory)
            : m_engine(engine), m_factory(factory) {}

        [[nodiscard]] auto create(const std::string& text, FontType fontType) const -> std::unique_ptr<TextEntity> {
            return std::make_unique<TextEntity>(m_engine, m_factory, fontType, text);
        }

    private:
        const TextEngine& m_engine;
        const FontFactory& m_factory;
    };
}
