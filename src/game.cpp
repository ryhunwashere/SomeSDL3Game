#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdexcept>
#include <memory>

#include "game.h"
#include "manager_scene.h"

rgp::Game::Game() :
    m_renderer(),
    m_textureEngine(m_renderer),
    m_textEngine(m_renderer),
    m_inputEngine(),
    m_sceneManager(m_inputEngine, m_renderer, m_textureEngine)
{
    SDL_Log("Game manager and subsystems initialized.");
}

rgp::Game::~Game() {
    SDL_Quit();
    SDL_Log("Game manager and subsystems unloaded.");
}

void rgp::Game::handleEvent(SDL_Event* event) {
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
