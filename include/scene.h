#pragma once
#include "interface_drawable.h"
#include "interface_updatable.h"

namespace rgp {
    class SceneManager;
    class InputEngine;
    class RendererEngine;

    class Scene : public IDrawable, public IUpdatable {
    public:
        Scene(SceneManager& sceneManager, InputEngine& inputEngine, RendererEngine& renderer)
            : m_sceneManager(sceneManager), m_inputEngine(inputEngine), m_renderer(renderer) {}

        ~Scene() override = default;

    protected:
        SceneManager& m_sceneManager;
        InputEngine& m_inputEngine;
        RendererEngine& m_renderer;
    };
}