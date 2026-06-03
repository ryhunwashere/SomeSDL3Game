#pragma once
#include <SDL3/SDL.h>
#include <string>

namespace engine {
    class RendererEngine {
    public:
        static RendererEngine& get()
        {
            static RendererEngine s_instance;
            return s_instance;
        }

        bool init(const std::string& title, int width, int height);
        void clear(float red, float green, float blue);
        void clear(float red, float green, float blue, float alpha);
        void present();
        void shutdown();

        SDL_Renderer* getRenderer() const;

        // Prevent copying and moving
        RendererEngine(const RendererEngine&) = delete;
        RendererEngine& operator=(const RendererEngine&) = delete;
        RendererEngine(RendererEngine&&) = delete;
        RendererEngine& operator=(RendererEngine&&) = delete;

    private:
        RendererEngine() = default;
        SDL_Window* m_window = nullptr;
        SDL_Renderer* m_renderer = nullptr;
        const char* NULL_RENDERER_ERROR = "Renderer is null";
        const char* NULL_WINDOW_ERROR = "Window is null";
    };
};