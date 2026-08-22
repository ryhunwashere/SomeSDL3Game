#pragma once
#include <cassert>
#include <functional>
#include <SDL3/SDL.h>

#include "except_sdl.h"
#include "constant/constant.h"

namespace rgp {
    struct Circle;
    constexpr auto OPAQUE_F  = constant::color::OPAQUE_F;

    class RendererEngine {
    public:
        static constexpr int LOGICAL_WIDTH  = 1920;
        static constexpr int LOGICAL_HEIGHT = 1080;

        RendererEngine();
        ~RendererEngine();

        void drawScreen(const ColorF& colorF) const {
            drawRect(colorF, nullptr);
        };

        void drawScreen(SDL_Texture* texture) const {
            drawTexture(nullptr, texture, 0.0, OPAQUE_F.a);
        };

        void drawRect(const ColorF& colorF, const SDL_FRect* dstrect) const;

        void drawTexture(const SDL_FRect* destRect, SDL_Texture* texture) const {
            drawTexture(destRect, texture, 0.0, OPAQUE_F.a);
        }

        void drawTexture(const SDL_FRect* destRect, SDL_Texture* texture, const double angle) const {
            drawTexture(destRect, texture, angle, OPAQUE_F.a);
        }

        void drawTexture(const SDL_FRect* destRect, SDL_Texture* texture, double angle, float alpha) const;

        void drawViewport(const SDL_Rect* destRect, std::invocable auto&& drawCallback) const {
            SDL_Rect currentViewport;
            SDL_GetRenderViewport(m_renderer, &currentViewport);

            const bool isViewportChanged = destRect != nullptr &&
                (currentViewport.x != destRect->x
                    || currentViewport.y != destRect->y
                    || currentViewport.w != destRect->w
                    || currentViewport.h != destRect->h);

            if (!isViewportChanged) return;

            if (!SDL_SetRenderViewport(m_renderer, destRect)) [[unlikely]]
                throw SDLException("Viewport render set error");

            std::invoke(std::forward<decltype(drawCallback)>(drawCallback));

            if (!SDL_SetRenderViewport(m_renderer, nullptr)) [[unlikely]]
                throw SDLException("Viewport render set error");
        }

        void drawCircleOutline(const Circle& circle, int segments, Color color);

        void clearAndPresent(std::invocable auto &&drawCallback) const {
            assert(m_renderer && NULL_RENDERER_ERROR);

            if (!SDL_RenderClear(m_renderer))
                throw SDLException("Render clear error");

            std::invoke(std::forward<decltype(drawCallback)>(drawCallback));

            if (!SDL_RenderPresent(m_renderer))
                throw SDLException("Render present error");
        }
        [[nodiscard]] auto getRenderer() const -> SDL_Renderer*;

    private:
        std::vector<SDL_FPoint> m_circlePointsBuffer;
        SDL_Window* m_window        = nullptr;
        SDL_Renderer* m_renderer    = nullptr;
        static constexpr auto NULL_RENDERER_ERROR  = "Renderer is null";
        static constexpr auto NULL_WINDOW_ERROR    = "Window is null";
    };
}
