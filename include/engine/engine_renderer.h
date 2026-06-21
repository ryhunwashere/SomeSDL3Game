#pragma once
#include <functional>
#include <SDL3/SDL.h>

#include "constant/constant.h"
#include "type/type_color.h"

namespace rgp {
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

        void drawViewport(const SDL_Rect* destRect, const std::function<void()>& drawCallback) const;

        void present() const;
        void clear() const;
        [[nodiscard]] auto getRenderer() const -> SDL_Renderer*;

    private:
        SDL_Window* m_window        = nullptr;
        SDL_Renderer* m_renderer    = nullptr;
    };
}
