#pragma once
#include "interface/interface_updatable.h"
#include "interface/interface_drawable.h"

#include "engine/engine_renderer.h"
#include "engine/engine_texture.h"
#include "engine/engine_input.h"

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
        RendererEngine m_renderer;
        TextureEngine m_textureEngine;
        InputEngine m_inputEngine;

        SceneManager m_sceneManager;
    };
}