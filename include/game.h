#pragma once
#include "game_context.h"
#include "interface/interface_drawable.h"
#include "manager/manager_scene.h"

namespace rgp {
    class Game final : public IDrawable {
    public:
        Game();
        ~Game() override;

        auto update() -> bool;
        void draw() override;
        void handleEvent(const SDL_Event* event);

    private:
        GameContext m_ctx;
        SceneManager m_sceneManager;
    };
}