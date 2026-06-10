#pragma once
#include <unordered_map>
#include <memory>
#include <functional>
#include "scene.h"
#include "engine_texture.h"

namespace rgp {
    class InputEngine;
    class RendererEngine;

    class SceneManager {
    public:
        SceneManager(InputEngine& inputEngine, RendererEngine& renderer, TextureEngine& textureEngine);
        ~SceneManager();

        enum SceneEnum { MAIN_MENU, LEVEL_ONE };

        void changeScene(SceneEnum targetScene);    
        void updateCurrentScene() const;
        void drawCurrentScene() const;

    private:
        std::unique_ptr<Scene> m_currentScene;
        std::unordered_map<SceneEnum, std::function<std::unique_ptr<Scene>()>> m_sceneMap;
    };
}