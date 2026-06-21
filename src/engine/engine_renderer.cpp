#include <SDL3/SDL.h>
#include "except_sdl.h"
#include "engine/engine_renderer.h"
#include <cassert>

constexpr auto WINDOW_TITLE         = "This is a window";
constexpr auto NULL_RENDERER_ERROR  = "Renderer is null";
constexpr auto NULL_WINDOW_ERROR    = "Window is null";

rgp::RendererEngine::RendererEngine() {
    if (!SDL_InitSubSystem(SDL_INIT_VIDEO))
        throw SDLException("SDL video initialization failure");

    const SDL_DisplayID displayID = SDL_GetPrimaryDisplay();
    if (displayID == 0)
        throw SDLException("Failed to get primary display");

    const SDL_DisplayMode* mode = SDL_GetDesktopDisplayMode(displayID);
    if (!mode)
        throw SDLException("Failed to get desktop display mode");

    const int targetWidth   = mode->w;
    const int targetHeight  = mode->h;

    m_window = SDL_CreateWindow(WINDOW_TITLE, targetWidth, targetHeight, SDL_WINDOW_FULLSCREEN);
    if (!m_window)
        throw SDLException("Window initialization failed");

    SDL_Log("Window initialized: %dx%d", targetWidth, targetHeight);

    const SDL_PropertiesID props = SDL_CreateProperties();
    SDL_SetPointerProperty(props, SDL_PROP_RENDERER_CREATE_WINDOW_POINTER, m_window);
    m_renderer = SDL_CreateRendererWithProperties(props);
    SDL_DestroyProperties(props);

    if (!m_renderer) {
        SDL_DestroyWindow(m_window);
        throw SDLException("Renderer initialization failed");
    }

    if (!SDL_SetRenderVSync(m_renderer, 1))
        throw SDLException("VSync setting failed");

    if (!SDL_SetRenderLogicalPresentation(m_renderer, targetWidth, targetHeight, SDL_LOGICAL_PRESENTATION_LETTERBOX))
        throw SDLException("Set renderer failed");

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
        throw SDLException("Set render draw color error");

    if (!SDL_RenderFillRect(m_renderer, dstrect))
        throw SDLException("Render fill rect error");
}

void rgp::RendererEngine::drawTexture(const SDL_FRect* destRect, SDL_Texture* texture, const double angle, const float alpha) const {
    assert(m_renderer && NULL_RENDERER_ERROR);

    if (!SDL_SetTextureColorModFloat(texture, OPAQUE_F.r, OPAQUE_F.g, OPAQUE_F.b) ||
        !SDL_SetTextureAlphaModFloat(texture, alpha)) {
        throw SDLException("Set texture mod error");
    }

    if (!SDL_RenderTextureRotated(m_renderer, texture, nullptr, destRect, angle, nullptr, SDL_FLIP_NONE))
        throw SDLException("Render texture error");
}

void rgp::RendererEngine::present() const {
    assert(m_renderer && NULL_RENDERER_ERROR);

    if (!SDL_RenderPresent(m_renderer))
        throw SDLException("Render present error");
}

void rgp::RendererEngine::clear() const {
    assert(m_renderer && NULL_RENDERER_ERROR);

    if (!SDL_RenderClear(m_renderer))
        throw SDLException("Render clear error");
}
