#include "engine/engine_text.h"
#include "except_sdl.h"

rgp::TextEngine::TextEngine(const RendererEngine& renderer) {
    if (!TTF_Init())
        throw SDLException("TTF init failed");

    m_engine = TTF_CreateRendererTextEngine(renderer.getRenderer());

    if (!m_engine)
        throw SDLException("Text engine creation failed");
}

rgp::TextEngine::~TextEngine() {
    TTF_DestroyRendererTextEngine(m_engine);
    TTF_Quit();
}
