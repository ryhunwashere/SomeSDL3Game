#define SDL_MAIN_USE_CALLBACKS 1

#include <stdexcept>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <memory>
#include "game.h"

#ifdef NDEBUG
    #include "util_logger.h"
#endif

std::unique_ptr<rgp::Game> game;

auto SDL_AppInit([[maybe_unused]] void** appstate, [[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) -> SDL_AppResult {
    try {
        game = std::make_unique<rgp::Game>();
        return SDL_APP_CONTINUE;

    } catch (const std::runtime_error& err) {
        SDL_SetError("[ERROR] Init error: \n\t%s", err.what());
        return SDL_APP_FAILURE;
    }
}

auto SDL_AppEvent([[maybe_unused]] void* appstate, SDL_Event* event) -> SDL_AppResult {
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

auto SDL_AppIterate([[maybe_unused]] void* appstate) -> SDL_AppResult {
    try {
        game->update();
        game->draw();

        return SDL_APP_CONTINUE;

    } catch (const std::runtime_error& err) {
        SDL_SetError("[ERROR] Iterate error: \n\t%s", err.what());
        return SDL_APP_FAILURE;
    }
}

void SDL_AppQuit([[maybe_unused]] void* appstate, const SDL_AppResult result) {
    if (result != SDL_APP_SUCCESS) {
#ifdef NDEBUG
        rgp::Util::logMessage(SDL_GetError());
#else
        SDL_Log("%s", SDL_GetError());
#endif
    }

    SDL_Log("App result: %s", result == SDL_APP_SUCCESS ? "SUCCESS" : "FAILED");
}