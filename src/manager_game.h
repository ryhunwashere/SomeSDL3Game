#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "entity_text.h"
#include "interface_updatable.h"
#include "interface_drawable.h"

namespace manager 
{
    class GameManager : public interface::IUpdatable, public interface::IDrawable
    {
    public:
        static GameManager& get();

        GameManager();
        ~GameManager();

        void handleEvent(SDL_Event* event);
        void update() override;
        void draw() override;

    private:
        std::unique_ptr<entity::TextEntity> m_timerText;
        float m_timerTextSpeed = 5.0f;
        char m_textBuffer[256]{};
    };
};