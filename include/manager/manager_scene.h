#pragma once
#include <unordered_map>
#include <memory>
#include <functional>

#include "entity/entity_text.h"
#include "scene/scene.h"
#include "enum/enum_scenetype.h"

namespace rgp {
    class GameContext;

    class SceneManager {
    public:
        explicit SceneManager(GameContext& ctx);
        ~SceneManager();

        void changeScene(SceneType targetScene);
        auto updateCurrentScene() const -> bool;
        void drawCurrentScene() const;

    private:
        std::unordered_map<SceneType, std::function<std::unique_ptr<Scene>()>> m_sceneMap;
        std::unique_ptr<Scene> m_currentScene;
        GameContext& m_ctx;

        // for displaying fps
        std::unique_ptr<TextEntity> m_fpsText;
        static constexpr float s_alpha  = 0.01f;
        float m_smoothedFps             = 60.0f;
    };
}
