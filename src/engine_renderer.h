#pragma once
#include <SDL3/SDL.h>
#include <string>
#include <memory>
#include "abstract_singleton.h"

namespace engine {
    class RendererEngine : public abstract::Singleton<RendererEngine> {
        friend class abstract::Singleton<RendererEngine>;

    public:
        void clear(float red, float green, float blue, float alpha);
        void clear(float red, float green, float blue);
        void present();
        [[nodiscard]] auto getRenderer() const -> SDL_Renderer*;

    private:
        RendererEngine();
        ~RendererEngine();

        SDL_Window* m_window        = nullptr;
        SDL_Renderer* m_renderer    = nullptr;
    };
}