#pragma once
#include "interface_updatable.h"
#include "interface_drawable.h"

#include "engine_renderer.h"
#include "engine_texture.h"
#include "engine_text.h"
#include "engine_input.h"

#include "manager_scene.h"

namespace rgp {
    class Game : public IUpdatable, public IDrawable {

    public:
        Game();
        ~Game() override;

        void update() override;
        void draw() override;
        void handleEvent(SDL_Event* event);

    private:
        RendererEngine m_renderer;
        TextureEngine m_textureEngine;
        TextEngine m_textEngine;
        InputEngine m_inputEngine;

        SceneManager m_sceneManager;
    };
};