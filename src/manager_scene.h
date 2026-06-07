#pragma once
#include <unordered_map>
#include <memory>
#include <functional>
#include "abstract_singleton.h"
#include "interface_drawable.h"
#include "interface_updatable.h"
#include "scene.h"

namespace rgp {
    class SceneManager : public Singleton<SceneManager> {
        friend class Singleton<SceneManager>;

    public:
        enum SceneEnum { MAIN_MENU, LEVEL_ONE };

        void changeScene(SceneEnum targetScene);    
        void updateCurrentScene();
        void drawCurrentScene();

    private:
        SceneManager();
        ~SceneManager();

        std::unique_ptr<Scene> m_currentScene;
        std::unordered_map<SceneEnum, std::function<std::unique_ptr<Scene>()>> m_sceneMap;
    };
};