#define SDL_MAIN_USE_CALLBACKS 1

#include <stdexcept>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "game.h"

#ifdef NDEBUG
    #include "util/util_logger.h"
#endif

auto SDL_AppInit(void** appstate, [[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) -> SDL_AppResult {
    try {
        *appstate = new rgp::Game();
        return SDL_APP_CONTINUE;
    } catch (...) {
        SDL_Log("[ERROR] Init error: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
}

auto SDL_AppEvent(void* appstate, SDL_Event* event) -> SDL_AppResult {
    auto* game = static_cast<rgp::Game*>(appstate);
    try {
        if (event->type == SDL_EVENT_QUIT || (event->type == SDL_EVENT_KEY_DOWN && event->key.key == SDLK_ESCAPE))
            return SDL_APP_SUCCESS;

        game->handleEvent(event);
        return SDL_APP_CONTINUE;

    } catch (const std::runtime_error& err) {
        SDL_SetError("[ERROR] Handle event error: \n\t%s", err.what());
        return SDL_APP_FAILURE;
    }
}

auto SDL_AppIterate(void* appstate) -> SDL_AppResult {
    auto* game = static_cast<rgp::Game*>(appstate);
    try {
        game->update();
        game->draw();
        return SDL_APP_CONTINUE;
    } catch (const std::runtime_error& err) {
        SDL_SetError("[ERROR] Iterate error: \n\t%s", err.what());
        return SDL_APP_FAILURE;
    }
}

void SDL_AppQuit(void* appstate, const SDL_AppResult result) {
    SDL_Log("Quitting game...");

    if (appstate) {
        const auto* game = static_cast<rgp::Game*>(appstate);
        delete game;
    }

    SDL_Quit();

    if (result != SDL_APP_SUCCESS) {
#ifdef NDEBUG
        rgp::Util::logMessage(SDL_GetError());
#else
        SDL_Log("%s", SDL_GetError());
#endif
    }
    SDL_Log("App result: %s", result == SDL_APP_SUCCESS ? "SUCCESS" : "FAILED");
}