#include <SDL3/SDL.h>

#include "game.h"
#include "manager/manager_scene.h"

rgp::Game::Game() : m_sceneManager(m_ctx) {
    SDL_Log("Game manager and subsystems initialized.");
}

rgp::Game::~Game() {
    SDL_Log("Unloading game...");
}

void rgp::Game::handleEvent(const SDL_Event* event) {
    if (event->type == SDL_EVENT_KEY_DOWN) 
        m_ctx.getInputManager().updateKeyDownState(event->key.scancode, true);
    else if (event->type == SDL_EVENT_KEY_UP) 
        m_ctx.getInputManager().updateKeyDownState(event->key.scancode, false);
}

auto rgp::Game::update() -> bool {
    m_ctx.getTimeManager().updateDeltaTime();

    if (!m_sceneManager.updateCurrentScene()) return false;

    m_ctx.getInputManager().keepTrackOfPreviousState();
    return true;
}

void rgp::Game::draw() {
    m_ctx.getRendererEngine().clear();

    m_sceneManager.drawCurrentScene();

    m_ctx.getRendererEngine().present();
}
