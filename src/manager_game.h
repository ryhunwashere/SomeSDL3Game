#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <memory>
#include <array>
#include "interface_updatable.h"
#include "interface_drawable.h"
#include "abstract_singleton.h"
#include "entity_text.h"

namespace manager {
    class GameManager : public abstract::Singleton<GameManager>, public interface::IUpdatable, public interface::IDrawable {
        friend class abstract::Singleton<GameManager>;

    public:
        void handleEvent(SDL_Event* event);
        void update() override;
        void draw() override;

    private:
        GameManager();
        ~GameManager() override;

        std::unique_ptr<entity::TextEntity> m_timerText;
        std::array<char, 32> m_textBuffer{};
    };
};