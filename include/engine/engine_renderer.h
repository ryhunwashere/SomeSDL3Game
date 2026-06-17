#pragma once
#include <SDL3/SDL.h>

#include "type/type_color.h"

namespace rgp {
    class RendererEngine {
    public:
        RendererEngine();
        ~RendererEngine();

        void drawScreen(const ColorF& colorF) const;
        void drawRect(const ColorF& colorF, const SDL_FRect* dstrect) const;
        void drawTexture(const ColorF& colorF, const SDL_FRect* dstrect, SDL_Texture* texture) const;

        void present() const;
        void clear() const;
        [[nodiscard]] auto getRenderer() const -> SDL_Renderer*;

    private:
        SDL_Window* m_window        = nullptr;
        SDL_Renderer* m_renderer    = nullptr;
    };
}
