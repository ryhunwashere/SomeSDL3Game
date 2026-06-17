#include <SDL3/SDL.h>
#include <stdexcept>
#include "engine/engine_renderer.h"
#include <cassert>

constexpr int WINDOW_WIDTH      = 800;
constexpr int WINDOW_HEIGHT     = 600;
auto WINDOW_TITLE               = "This is a window";
auto NULL_RENDERER_ERROR        = "Renderer is null";
auto NULL_WINDOW_ERROR          = "Window is null";

rgp::RendererEngine::RendererEngine() {
    if (!SDL_InitSubSystem(SDL_INIT_VIDEO))
        throw std::runtime_error(
            std::string("SDL video initialization failure: ") + SDL_GetError()
        );

    m_window = SDL_CreateWindow(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
    if (!m_window)
        throw std::runtime_error(
            std::string("Window initialization failed: ") + SDL_GetError()
        );

    SDL_Log("Window initialized.");

    const SDL_PropertiesID props = SDL_CreateProperties();
    SDL_SetPointerProperty(props, SDL_PROP_RENDERER_CREATE_WINDOW_POINTER, m_window);
    m_renderer = SDL_CreateRendererWithProperties(props);
    SDL_DestroyProperties(props);

    if (!m_renderer) {
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

    SDL_Log("Renderer initialized.");
}

rgp::RendererEngine::~RendererEngine() {
    if (m_renderer) {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
        SDL_Log("Renderer unloaded.");
    }

    if (m_window) {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
        SDL_Log("Window unloaded.");
    }
}

auto rgp::RendererEngine::getRenderer() const -> SDL_Renderer* {
    assert(m_renderer && NULL_RENDERER_ERROR);
    return m_renderer;
}

void rgp::RendererEngine::drawScreen(const ColorF& colorF) const {
    drawRect(colorF, nullptr);
}

void rgp::RendererEngine::drawRect(const ColorF& colorF, const SDL_FRect* dstrect) const {
    assert(m_renderer && NULL_RENDERER_ERROR);

    if (!SDL_SetRenderDrawColorFloat(m_renderer, colorF.r, colorF.g, colorF.b, colorF.a))
        throw std::runtime_error(std::string(SDL_GetError()));

    if (!SDL_RenderFillRect(m_renderer, dstrect))
        throw std::runtime_error(std::string(SDL_GetError()));
}

void rgp::RendererEngine::drawTexture(const ColorF& colorF, const SDL_FRect* dstrect, SDL_Texture* texture) const {
    assert(m_renderer && NULL_RENDERER_ERROR);

    if (!SDL_SetTextureColorModFloat(texture, colorF.r, colorF.g, colorF.b) ||
        !SDL_SetTextureAlphaModFloat(texture, colorF.a)) {
        throw std::runtime_error(
            std::string("Set texture mod error: ") + SDL_GetError()
        );
    }

    if (!SDL_RenderTexture(m_renderer, texture, nullptr, dstrect))
        throw std::runtime_error(
            std::string("Render texture error: ") + SDL_GetError()
        );
}

void rgp::RendererEngine::present() const {
    assert(m_renderer && NULL_RENDERER_ERROR);

    if (!SDL_RenderPresent(m_renderer))
        throw std::runtime_error(
            std::string("Render present error: ") + SDL_GetError()
        );
}

void rgp::RendererEngine::clear() const {
    assert(m_renderer && NULL_RENDERER_ERROR);

    if (!SDL_RenderClear(m_renderer))
        throw std::runtime_error(
            std::string("Render clear error: ") + SDL_GetError()
        );
}
