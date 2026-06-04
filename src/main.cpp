#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL_main.h>
#include <stdexcept>
#include "manager_game.h"

auto SDL_AppInit([[maybe_unused]] void** appstate, [[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) -> SDL_AppResult {
    try {
        manager::GameManager::get();
        return SDL_APP_CONTINUE;

    } catch (const std::runtime_error& err) {
        SDL_Log("Error: %s", err.what());
        return SDL_APP_FAILURE;
    }
}

auto SDL_AppEvent([[maybe_unused]] void* appstate, SDL_Event* event) -> SDL_AppResult {
    if (event->type == SDL_EVENT_QUIT 
        || (event->type == SDL_EVENT_KEY_DOWN && event->key.key == SDLK_ESCAPE))
        return SDL_APP_SUCCESS;

    manager::GameManager::get().handleEvent(event);

    return SDL_APP_CONTINUE;
}

auto SDL_AppIterate([[maybe_unused]] void* appstate) -> SDL_AppResult {
    manager::GameManager::get().update();
    manager::GameManager::get().draw();

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit([[maybe_unused]] void* appstate, SDL_AppResult result) {
    SDL_Log("App result: %s", result == SDL_APP_SUCCESS ? "SUCCESS" : "FAILED");
}