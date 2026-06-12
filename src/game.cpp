#include <SDL3/SDL.h>

#include "game.h"
#include "manager/manager_scene.h"

rgp::Game::Game() :
    m_textureEngine(m_renderer),
    m_textEngine(m_renderer),
    m_textFactory(m_textEngine, m_fontFactory),
    m_ctx{
        .renderer       = m_renderer,
        .textureEngine  = m_textureEngine,
        .textEngine     = m_textEngine,
        .inputEngine    = m_inputEngine,
        .fontFactory    = m_fontFactory,
        .textFactory    = m_textFactory,
    },
    m_sceneManager(m_ctx)
{
    SDL_Log("Game manager and subsystems initialized.");
}

rgp::Game::~Game() {
    SDL_Quit();
    SDL_Log("Game manager and subsystems unloaded.");
}

void rgp::Game::handleEvent(const SDL_Event* event) {
    if (event->type == SDL_EVENT_KEY_DOWN) 
        m_inputEngine.updateKeyDownState(event->key.scancode, true);
    else if (event->type == SDL_EVENT_KEY_UP) 
        m_inputEngine.updateKeyDownState(event->key.scancode, false);
}

void rgp::Game::update() {
    m_sceneManager.updateCurrentScene();
    m_inputEngine.keepTrackOfPreviousState();
}

void rgp::Game::draw() {
    m_renderer.clear();

    m_sceneManager.drawCurrentScene();

    m_renderer.present();
}
