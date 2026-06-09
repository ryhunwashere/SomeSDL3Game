#pragma once
#include <SDL3/SDL.h>

namespace rgp {
    class RendererEngine {
    public:
        RendererEngine();
        ~RendererEngine();

        void draw(float red, float green, float blue, float alpha);
        void draw(float red, float green, float blue, float alpha, SDL_Texture* texture, const SDL_FRect* dstrect);
        void present();
        void clear();
        [[nodiscard]] auto getRenderer() const -> SDL_Renderer*;

    private:
        SDL_Window* m_window        = nullptr;
        SDL_Renderer* m_renderer    = nullptr;
    };
}