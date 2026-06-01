// main.cpp
#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL_main.h>
#include "game.h"

SDL_AppResult SDL_AppInit(void** appstate, [[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    Game* game_context = new Game();

    if (!game_context->initialize()) 
    {
        delete game_context;
        SDL_Log("SDL Error: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // Store instance state
    *appstate = game_context;

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    Game* game_context = static_cast<Game*>(appstate);

    if (event->type == SDL_EVENT_QUIT 
        || (event->type == SDL_EVENT_KEY_DOWN && event->key.key == SDLK_ESCAPE))
        return SDL_APP_SUCCESS;

    game_context->handle_event(event);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate)
{
    Game* game_context = static_cast<Game*>(appstate);
    game_context->update();
    game_context->render();

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, [[maybe_unused]] SDL_AppResult result)
{
    if (appstate) 
    {
        Game* game_context = static_cast<Game*>(appstate);
        game_context->shutdown();
        delete game_context;
    }
}