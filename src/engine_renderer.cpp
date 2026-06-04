#include <SDL3/SDL.h>
#include <stdexcept>
#include "engine_renderer.h"

using namespace engine;

constexpr int WINDOW_WIDTH      = 800;
constexpr int WINDOW_HEIGHT     = 600;
const char* WINDOW_TITLE        = "This is a window";
const char* NULL_RENDERER_ERROR = "Renderer is null";
const char* NULL_WINDOW_ERROR   = "Window is null";

RendererEngine::RendererEngine()
{
    m_window = SDL_CreateWindow(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
    if (!m_window)
        throw std::runtime_error(
            std::string("Window initialization failed: ") + SDL_GetError()
        );

    SDL_PropertiesID props = SDL_CreateProperties();
    SDL_SetPointerProperty(props, SDL_PROP_RENDERER_CREATE_WINDOW_POINTER, m_window);
    m_renderer = SDL_CreateRendererWithProperties(props);
    SDL_DestroyProperties(props);

    if (!m_renderer) 
    {
        SDL_DestroyWindow(m_window);
        throw std::runtime_error(
            std::string("Renderer initialization failed: ") + SDL_GetError()
        );
    }

    if (!SDL_SetRenderVSync(m_renderer, 1))
        throw std::runtime_error(
            std::string("VSync setting failed: ") + SDL_GetError()
        );

    if (!SDL_SetRenderLogicalPresentation(m_renderer, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_LOGICAL_PRESENTATION_LETTERBOX))
        throw std::runtime_error(
            std::string("Set renderer failed: ") + SDL_GetError()
        );

    SDL_Log("RendererEngine resources initialized.");
}

RendererEngine::~RendererEngine()
{
    if (m_renderer) SDL_DestroyRenderer(m_renderer);
    if (m_window) SDL_DestroyWindow(m_window);
    SDL_Log("RendererEngine resources unloaded.");
}

RendererEngine& RendererEngine::get()
{
    static RendererEngine instance;
    return instance;
}

void RendererEngine::clear(float red, float green, float blue, float alpha)
{
    if (!m_renderer)
        throw std::runtime_error(NULL_RENDERER_ERROR);

    if (!SDL_SetRenderDrawColorFloat(m_renderer, red, green, blue, alpha))
        throw std::runtime_error(
            std::string("Set draw color error: ") + SDL_GetError()
        );

    if (!SDL_RenderClear(m_renderer))
        throw std::runtime_error(
            std::string("Render clear error: ") + SDL_GetError()
        );
}

void RendererEngine::clear(float red, float green, float blue)
{
    RendererEngine::clear(red, green, blue, SDL_ALPHA_OPAQUE_FLOAT);
}

void RendererEngine::present()
{
    if (!m_renderer)
        throw std::runtime_error(NULL_RENDERER_ERROR);

    if (!SDL_RenderPresent(m_renderer))
        throw std::runtime_error(
            std::string("Render present error: ") + SDL_GetError()
        );
}

SDL_Renderer* RendererEngine::getRenderer() const
{
    if (!m_renderer)
        throw std::runtime_error(NULL_RENDERER_ERROR);

    return m_renderer;
}
