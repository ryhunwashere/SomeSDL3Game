#include <SDL3/SDL.h>
#include "engine_renderer.h"

using namespace engine;

bool RendererEngine::initialize(const std::string& title, int width, int height) 
{
    m_window = SDL_CreateWindow(title.c_str(), width, height, SDL_WINDOW_RESIZABLE);

    if (!m_window) return false;

    SDL_PropertiesID props = SDL_CreateProperties();
    SDL_SetPointerProperty(props, SDL_PROP_RENDERER_CREATE_WINDOW_POINTER, m_window);
    m_renderer = SDL_CreateRendererWithProperties(props);
    SDL_DestroyProperties(props);

    if (!m_renderer) return false;

    SDL_SetRenderVSync(m_renderer, 1);
    SDL_SetRenderLogicalPresentation(m_renderer, width, height, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    return true;
}

void RendererEngine::clear(float red, float green, float blue, float alpha)
{
    SDL_SetRenderDrawColorFloat(m_renderer, red, green, blue, alpha);
    SDL_RenderClear(m_renderer);
}

void RendererEngine::clear(float red, float green, float blue)
{
    RendererEngine::clear(red, green, blue, SDL_ALPHA_OPAQUE_FLOAT);
}

void RendererEngine::present()
{
    SDL_RenderPresent(m_renderer);
}

void RendererEngine::shutdown()
{
    if (m_renderer) SDL_DestroyRenderer(m_renderer);
    if (m_window) SDL_DestroyWindow(m_window);
}