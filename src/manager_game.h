#pragma once
#include <memory>
#include <array>
#include "interface_updatable.h"
#include "interface_drawable.h"
#include "abstract_singleton.h"
#include "entity_text.h"
#include "entity_player.h"

namespace rgp {
    class GameManager : public Singleton<GameManager>, public IUpdatable, public IDrawable {
        friend class Singleton<GameManager>;

    public:
        void update() override;
        void draw() override;
        void handleEvent(SDL_Event* event);

    private:
        GameManager();
        ~GameManager() override;
    };
};