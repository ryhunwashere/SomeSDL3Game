#pragma once
#include <SDL3_ttf/SDL_ttf.h>
#include "engine_renderer.h"

namespace rgp {
    class TextEngine {
    public:
        explicit TextEngine(const RendererEngine& renderer);
        ~TextEngine();

        [[nodiscard]] auto getEnginePtr() const -> TTF_TextEngine* { return m_engine; }

    private:
        TTF_TextEngine* m_engine;
    };
}
