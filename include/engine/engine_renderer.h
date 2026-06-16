#pragma once
#include <SDL3/SDL.h>

#include "type/type_color.h"

namespace rgp {
    class RendererEngine {
    public:
        RendererEngine();
        ~RendererEngine();

        void draw(const ColorF& colorF) const;
        void draw(const ColorF& colorF, SDL_Texture* texture, const SDL_FRect* dstrect) const;
        void present() const;
        void clear() const;
        [[nodiscard]] auto getRenderer() const -> SDL_Renderer*;

    private:
        SDL_Window* m_window        = nullptr;
        SDL_Renderer* m_renderer    = nullptr;
    };
}
