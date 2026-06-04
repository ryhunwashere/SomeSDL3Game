#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL_main.h>
#include <stdexcept>
#include <memory>
#include "manager_game.h"

SDL_AppResult SDL_AppInit(void** appstate, [[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    try {
        auto gameContext = std::make_unique<manager::GameManager>();
        *appstate = gameContext.release();

        return SDL_APP_CONTINUE;
    } catch (const std::runtime_error& err) {
        SDL_Log("Error: %s", err.what());
        *appstate = nullptr;

        return SDL_APP_FAILURE;
    }
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
    manager::GameManager* gameContext = static_cast<manager::GameManager*>(appstate);

    if (event->type == SDL_EVENT_QUIT 
        || (event->type == SDL_EVENT_KEY_DOWN && event->key.key == SDLK_ESCAPE))
        return SDL_APP_SUCCESS;

    gameContext->handleEvent(event);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate) {
    auto* gameContext = static_cast<manager::GameManager*>(appstate);

    gameContext->update();
    gameContext->draw();

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, [[maybe_unused]] SDL_AppResult result) {
    if (appstate)
        std::unique_ptr<manager::GameManager> gameContext(static_cast<manager::GameManager*>(appstate));
}