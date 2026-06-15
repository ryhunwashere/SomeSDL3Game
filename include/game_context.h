#pragma once
#include "manager/manager_audio.h"
#include "manager/manager_input.h"
#include "engine/engine_renderer.h"
#include "engine/engine_text.h"
#include "manager/manager_texture.h"
#include "factory/factory_font.h"
#include "factory/factory_text.h"
#include "manager/manager_time.h"

namespace rgp {
    class GameContext {
    public:
        GameContext() :
            m_textEngine(m_rendererEngine),
            m_textFactory(m_textEngine, m_fontFactory),
            m_textureManager(m_rendererEngine) {}

        [[nodiscard]] auto getRendererEngine()  -> RendererEngine&  { return m_rendererEngine; }
        [[nodiscard]] auto getTextEngine()      -> TextEngine&      { return m_textEngine; }
        [[nodiscard]] auto getFontFactory()     -> FontFactory&     { return m_fontFactory; }
        [[nodiscard]] auto getTextFactory()     -> TextFactory&     { return m_textFactory; }
        [[nodiscard]] auto getAudioManager()    -> AudioManager&    { return m_audioManager; }
        [[nodiscard]] auto getTextureManager()  -> TextureManager&  { return m_textureManager; }
        [[nodiscard]] auto getInputManager()    -> InputManager&    { return m_inputManager; }
        [[nodiscard]] auto getTimeManager()     -> TimeManager&     { return m_timeManager; }

    private:
        RendererEngine  m_rendererEngine;
        TextEngine      m_textEngine;
        FontFactory     m_fontFactory;
        TextFactory     m_textFactory;
        TextureManager  m_textureManager;
        InputManager    m_inputManager;
        AudioManager    m_audioManager;
        TimeManager     m_timeManager;
    };
}

