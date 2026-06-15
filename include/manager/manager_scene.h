#pragma once
#include <unordered_map>
#include <memory>
#include <functional>
#include "game_context.h"
#include "enum/enum_scenetype.h"
#include "scene/scene.h"
#include "entity/entity_text.h"

namespace rgp {
    class SceneManager {
    public:
        explicit SceneManager(GameContext& ctx);
        ~SceneManager();

        void changeScene(SceneType targetScene);
        void updateCurrentScene();
        void drawCurrentScene() const;

    private:
        GameContext& m_ctx;
        std::unique_ptr<Scene> m_currentScene;
        std::unordered_map<SceneType, std::function<std::unique_ptr<Scene>()>> m_sceneMap;

        // for displaying fps
        std::unique_ptr<TextEntity> m_fpsText;
        static constexpr float s_alpha  = 0.01f;
        float m_smoothedFps             = 60.0f;

        void updateFpsText();
    };
}
