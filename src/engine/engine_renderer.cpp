#include <SDL3/SDL.h>
#include "except_sdl.h"
#include "engine/engine_renderer.h"
#include <cassert>

constexpr auto WINDOW_TITLE         = "This is a window";
constexpr auto NULL_RENDERER_ERROR  = "Renderer is null";
constexpr auto NULL_WINDOW_ERROR    = "Window is null";
constexpr auto BLACK_OPAQUE_F       = rgp::constant::color::BLACK_OPAQUE_F;

rgp::RendererEngine::RendererEngine() {
    if (!SDL_InitSubSystem(SDL_INIT_VIDEO))
        throw SDLException("SDL video initialization failure");

    const SDL_DisplayID displayID = SDL_GetPrimaryDisplay();
    if (displayID == 0)
        throw SDLException("Failed to get primary display");

    const SDL_DisplayMode* mode = SDL_GetDesktopDisplayMode(displayID);
    if (!mode)
        throw SDLException("Failed to get desktop display mode");

    // Keep the window creation matching the actual physical monitor
    const int physicalWidth   = mode->w;
    const int physicalHeight  = mode->h;

    m_window = SDL_CreateWindow(WINDOW_TITLE, physicalWidth, physicalHeight, SDL_WINDOW_FULLSCREEN);
    if (!m_window)
        throw SDLException("Window initialization failed");

    SDL_Log("Window initialized at physical desktop resolution: %dx%d", physicalWidth, physicalHeight);

    const SDL_PropertiesID props = SDL_CreateProperties();
    SDL_SetPointerProperty(props, SDL_PROP_RENDERER_CREATE_WINDOW_POINTER, m_window);
    SDL_SetNumberProperty(props, SDL_PROP_RENDERER_MAX_TEXTURE_SIZE_NUMBER, 2048);
    m_renderer = SDL_CreateRendererWithProperties(props);
    SDL_DestroyProperties(props);

    if (!m_renderer) {
        SDL_DestroyWindow(m_window);
        throw SDLException("Renderer initialization failed");
    }

    if (!SDL_SetRenderVSync(m_renderer, 1))
        throw SDLException("VSync setting failed");

    if (!SDL_SetRenderLogicalPresentation(m_renderer, LOGICAL_WIDTH, LOGICAL_HEIGHT, SDL_LOGICAL_PRESENTATION_LETTERBOX))
        throw SDLException("Set renderer failed");

    SDL_Log("Renderer initialized with a 1080p Logical Canvas.");
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

void rgp::RendererEngine::drawRect(const ColorF& colorF, const SDL_FRect* dstrect) const {
    assert(m_renderer && NULL_RENDERER_ERROR);

    if (!SDL_SetRenderDrawColorFloat(m_renderer, colorF.r, colorF.g, colorF.b, colorF.a))
        throw SDLException("Set render draw color error");

    if (!SDL_RenderFillRect(m_renderer, dstrect))
        throw SDLException("Render fill rect error");
}

void rgp::RendererEngine::drawTexture(const SDL_FRect* destRect, SDL_Texture* texture, const double angle, const float alpha) const {
    assert(m_renderer && NULL_RENDERER_ERROR);

    if (!SDL_SetTextureColorModFloat(texture, OPAQUE_F.r, OPAQUE_F.g, OPAQUE_F.b)
        || !SDL_SetTextureAlphaModFloat(texture, alpha)
        || !SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_LINEAR)) {
        throw SDLException("Set texture mod error");
    }

    if (!SDL_RenderTextureRotated(m_renderer, texture, nullptr, destRect, angle, nullptr, SDL_FLIP_NONE))
        throw SDLException("Render texture error");
}

void rgp::RendererEngine::drawViewport(const SDL_Rect* destRect, const std::function<void()>& drawCallback) const {
    if (!SDL_SetRenderViewport(m_renderer, destRect))
        throw SDLException("Viewport render set error");

    drawCallback();

    if (!SDL_SetRenderViewport(m_renderer, nullptr))
        throw SDLException("Viewport render set error");
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
