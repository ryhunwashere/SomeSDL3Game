#include <stdexcept>
#include "engine/engine_text.h"

rgp::TextEngine::TextEngine(const RendererEngine& renderer) :
    m_engine(TTF_CreateRendererTextEngine(renderer.getRenderer()))
{
    if (!m_engine)
        throw std::runtime_error("Text engine creation failed: " + std::string(SDL_GetError()));
}

rgp::TextEngine::~TextEngine() {
    TTF_DestroyRendererTextEngine(m_engine);
    TTF_Quit();
}

