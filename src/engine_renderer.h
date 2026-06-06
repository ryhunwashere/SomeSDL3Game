#pragma once
#include <SDL3/SDL.h>
#include "abstract_singleton.h"

namespace rgp {
    class RendererEngine : public Singleton<RendererEngine> {
        friend class Singleton<RendererEngine>;

    public:
        void draw(float red, float green, float blue, float alpha);
        void draw(float red, float green, float blue, float alpha, SDL_Texture* texture, const SDL_FRect* dstrect);
        void present();
        void clear();
        [[nodiscard]] auto getRenderer() const -> SDL_Renderer*;

    private:
        RendererEngine();
        ~RendererEngine();

        SDL_Window* m_window        = nullptr;
        SDL_Renderer* m_renderer    = nullptr;
        SDL_FRect m_rect{ 0.0f, 0.0f, 0.0f, 0.0f };
    };
}