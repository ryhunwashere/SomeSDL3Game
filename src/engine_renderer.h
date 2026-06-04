#pragma once
#include <SDL3/SDL.h>
#include <string>
#include <memory>

namespace engine 
{
    class RendererEngine 
    {
    public:
        static RendererEngine& get();

        void clear(float red, float green, float blue, float alpha);
        void clear(float red, float green, float blue);
        void present();
        SDL_Renderer* getRenderer() const;

        RendererEngine(const RendererEngine&)               = delete;
        RendererEngine& operator=(const RendererEngine&)    = delete;
        RendererEngine(RendererEngine&&)                    = delete;
        RendererEngine& operator=(RendererEngine&&)         = delete;

    private:
        RendererEngine();
        ~RendererEngine();

        SDL_Window* m_window        = nullptr;
        SDL_Renderer* m_renderer    = nullptr;
    };
}