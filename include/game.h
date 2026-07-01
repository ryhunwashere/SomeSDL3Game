#pragma once
#include "game_context.h"
#include "manager/manager_scene.h"

namespace rgp {
    class Game final {
    public:
        Game();
        ~Game();

        auto update() -> bool;
        void draw();
        void handleEvent(const SDL_Event* event);

    private:
        GameContext m_ctx;
        SceneManager m_sceneManager;
    };
}