#include <SDL3/SDL.h>
#include "engine/engine_renderer.h"

#include <cmath>
#include <span>

#include "type/type_circle.h"

constexpr auto WINDOW_TITLE         = "This is a window";
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

    if (!SDL_SetRenderVSync(m_renderer, 0))
        throw SDLException("VSync setting failed");

    if (!SDL_SetRenderLogicalPresentation(m_renderer, LOGICAL_WIDTH, LOGICAL_HEIGHT, SDL_LOGICAL_PRESENTATION_LETTERBOX))
        throw SDLException("Set renderer failed");

    if (!SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND))
        throw SDLException("Set render blend mode error");

    SDL_Log("Renderer initialized with a 1080p Logical Canvas.");

    initCircleCache();
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

inline void rgp::RendererEngine::initCircleCache() {
    m_unitCircleCache.resize(CIRCLE_SEGMENTS + 1);

    constexpr float angleStep = 2.0f * std::numbers::pi_v<float> / static_cast<float>(CIRCLE_SEGMENTS);
    for (int i = 0; i < CIRCLE_SEGMENTS; ++i) {
        const float angle = static_cast<float>(i) * angleStep;
        m_unitCircleCache[i] = {.x = std::cos(angle), .y = std::sin(angle)};
    }
    m_unitCircleCache[CIRCLE_SEGMENTS] = m_unitCircleCache[0];

    m_circlePointsBuffer.reserve(64);
}

auto rgp::RendererEngine::getRenderer() const -> SDL_Renderer* {
    assert(m_renderer && NULL_RENDERER_ERROR);
    return m_renderer;
}

void rgp::RendererEngine::drawRect(const ColorF& colorF, const SDL_FRect* destRect) const {
    assert(m_renderer && NULL_RENDERER_ERROR);

    if (!SDL_SetRenderDrawColorFloat(m_renderer, colorF.r, colorF.g, colorF.b, colorF.a)) [[unlikely]]
        throw SDLException("Set render draw color error");

    if (!SDL_RenderFillRect(m_renderer, destRect)) [[unlikely]]
        throw SDLException("Render fill rect error");
}

void rgp::RendererEngine::drawTexture(const SDL_FRect* destRect, SDL_Texture* texture, const double angle, const float alpha) const {
    assert(m_renderer && NULL_RENDERER_ERROR);

    float currentAlpha = 1.0f;
    SDL_GetTextureAlphaModFloat(texture, &currentAlpha);

    if (currentAlpha != alpha)
        if (!SDL_SetTextureAlphaModFloat(texture, alpha)) [[unlikely]]
            throw SDLException("Set texture alpha error");

    if (!SDL_RenderTextureRotated(m_renderer, texture, nullptr, destRect, angle, nullptr, SDL_FLIP_NONE)) [[unlikely]]
        throw SDLException("Render texture error");
}

void rgp::RendererEngine::drawCircleOutline(const Circle& circle, const Color color) const {
    if (!SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a)) [[unlikely]]
        throw SDLException("Set draw color for circle failed");

    static constexpr int CIRCLE_POINTS = CIRCLE_SEGMENTS + 1;

    m_circlePointsBuffer.resize(CIRCLE_POINTS);

    for (size_t i = 0; i < CIRCLE_POINTS; ++i) {
        m_circlePointsBuffer[i].x = circle.x + m_unitCircleCache[i].x * circle.r;
        m_circlePointsBuffer[i].y = circle.y + m_unitCircleCache[i].y * circle.r;
    }

    if (!SDL_RenderLines(m_renderer, m_circlePointsBuffer.data(), CIRCLE_POINTS)) [[unlikely]]
        throw SDLException("Render lines for circle failed");
}

void rgp::RendererEngine::drawCircleOutlinesBatch(const std::span<const Circle> circles, const Color color) const {
    if (circles.empty()) return;

    if (!SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a)) [[unlikely]]
        throw SDLException("Set draw color for circles failed");

    static constexpr size_t POINTS_PER_CIRCLE = CIRCLE_SEGMENTS + 1;
    m_circlePointsBuffer.resize(POINTS_PER_CIRCLE);

    for (const auto& [x, y, r] : circles) {
        for (size_t i = 0; i < POINTS_PER_CIRCLE; ++i) {
            m_circlePointsBuffer[i].x = x + m_unitCircleCache[i].x * r;
            m_circlePointsBuffer[i].y = y + m_unitCircleCache[i].y * r;
        }

        if (!SDL_RenderLines(m_renderer, m_circlePointsBuffer.data(), POINTS_PER_CIRCLE)) [[unlikely]]
            throw SDLException("Render lines for bulk circles failed");
    }
}