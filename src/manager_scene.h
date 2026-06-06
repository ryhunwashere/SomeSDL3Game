#pragma once
#include <SDL3/SDL.h>
#include "abstract_singleton.h"
#include "interface_drawable.h"
#include "interface_updatable.h"
#include "interface_eventhandlable.h"

namespace rgp {
    class SceneManager : public Singleton<SceneManager>, public IUpdatable, public IDrawable, public IEventHandlable {
        friend class Singleton<SceneManager>;

    public:
        void update() override;
        void draw() override;
        void handleEvent(SDL_Event* event) override;

    private:
        SceneManager();
        ~SceneManager() override;
    };
};