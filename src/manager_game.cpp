#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdexcept>

#include "manager_game.h"
#include "manager_scene.h"

#include "engine_renderer.h"
#include "engine_input.h"
#include "engine_texture.h"
#include "engine_text.h"

rgp::GameManager::GameManager() {
    // ensure these are initiated first
    rgp::RendererEngine::get();
    rgp::TextureEngine::get();
    rgp::TextEngine::get();
    rgp::InputEngine::get();

    rgp::SceneManager::get();

    SDL_Log("GameManager and subsystems initialized.");
}

rgp::GameManager::~GameManager() {
    SDL_Quit();
    SDL_Log("GameManager and subsystems unloaded.");
}

void rgp::GameManager::handleEvent(SDL_Event* event) {
    auto& input = rgp::InputEngine::get();

    if (event->type == SDL_EVENT_KEY_DOWN) 
        input.updateKeyDownState(event->key.scancode, true);
    else if (event->type == SDL_EVENT_KEY_UP) 
        input.updateKeyDownState(event->key.scancode, false);
}

void rgp::GameManager::update() {
    rgp::SceneManager::get().updateCurrentScene();
    rgp::InputEngine::get().keepTrackOfPreviousState();
}

void rgp::GameManager::draw() {
    auto& renderer = rgp::RendererEngine::get();

    renderer.clear();

    rgp::SceneManager::get().drawCurrentScene();

    renderer.present();
}
