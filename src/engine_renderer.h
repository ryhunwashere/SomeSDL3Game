#pragma once
#include <SDL3/SDL.h>
#include <string>
#include <memory>

namespace engine {
    class RendererEngine {
    public:
        static auto get() -> RendererEngine&;

        void clear(float red, float green, float blue, float alpha);
        void clear(float red, float green, float blue);
        void present();
        [[nodiscard]] auto getRenderer() const -> SDL_Renderer*;

        RendererEngine(const RendererEngine&)                       = delete;
        auto operator=(const RendererEngine&) -> RendererEngine&    = delete;
        RendererEngine(RendererEngine&&)                            = delete;
        auto operator=(RendererEngine&&) -> RendererEngine&         = delete;

    private:
        RendererEngine();
        ~RendererEngine();

        SDL_Window* m_window        = nullptr;
        SDL_Renderer* m_renderer    = nullptr;
    };
}