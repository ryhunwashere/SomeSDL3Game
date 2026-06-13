#pragma once
#include <unordered_map>
#include <memory>
#include <functional>

#include "game_context.h"
#include "enum/enum_scenetype.h"
#include "scene/scene.h"

namespace rgp {
    class SceneManager {
    public:
        explicit SceneManager(const GameContext& ctx);
        ~SceneManager();

        void changeScene(SceneType targetScene);
        void updateCurrentScene();
        void drawCurrentScene() const;

    private:
        const GameContext& m_ctx;
        std::unique_ptr<Scene> m_currentScene;
        std::unordered_map<SceneType, std::function<std::unique_ptr<Scene>()>> m_sceneMap;
    };
}
