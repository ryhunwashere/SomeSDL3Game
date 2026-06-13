#pragma once
#include "engine/engine_input.h"
#include "engine/engine_renderer.h"
#include "engine/engine_text.h"
#include "engine/engine_texture.h"
#include "factory/factory_font.h"
#include "factory/factory_text.h"

namespace rgp {
    class GameContext {
    public:
        GameContext() :
            m_textureEngine(m_rendererEngine),
            m_textEngine(m_rendererEngine),
            m_textFactory(m_textEngine, m_fontFactory) {}

        [[nodiscard]] auto getRendererEngine()  -> RendererEngine&  { return m_rendererEngine; }
        [[nodiscard]] auto getTextureEngine()   -> TextureEngine&   { return m_textureEngine; }
        [[nodiscard]] auto getTextEngine()      -> TextEngine&      { return m_textEngine; }
        [[nodiscard]] auto getInputEngine()     -> InputEngine&     { return m_inputEngine; }
        [[nodiscard]] auto getFontFactory()     -> FontFactory&     { return m_fontFactory; }
        [[nodiscard]] auto getTextFactory()     -> TextFactory&     { return m_textFactory; }

    private:
        RendererEngine  m_rendererEngine;
        TextureEngine   m_textureEngine;
        TextEngine      m_textEngine;
        InputEngine     m_inputEngine;
        FontFactory     m_fontFactory;
        TextFactory     m_textFactory;
    };
}

