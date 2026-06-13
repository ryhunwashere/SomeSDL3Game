#pragma once
#include "game_context.h"

#include "interface/interface_updatable.h"
#include "interface/interface_drawable.h"

#include "engine/engine_renderer.h"

#include "manager/manager_scene.h"

namespace rgp {
    class Game : public IUpdatable, public IDrawable {
    public:
        Game();
        ~Game() override;

        void update() override;
        void draw() override;
        void handleEvent(const SDL_Event* event);

    private:
        GameContext m_ctx;
        SceneManager m_sceneManager;
    };
}