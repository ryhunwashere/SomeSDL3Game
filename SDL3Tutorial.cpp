#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <charconv>
#include <cmath>

constexpr int WINDOW_WIDTH = 640;
constexpr int WINDOW_HEIGHT = 480;
const char* WINDOW_NAME = "This is a window";

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static TTF_TextEngine* text_engine = NULL;
static TTF_Font* font = NULL;

static TTF_Text* text = NULL;
static char buffer[64];
static float font_size = 24.0f;

static float text_x = 100.0f;
static float text_y = 100.0f;
constexpr float MOVE_SPEED = 4.0f;

static struct {
    bool w = false;
    bool a = false;
    bool s = false;
    bool d = false;
} keys;

static SDL_AppResult InitWindow()
{
    window = SDL_CreateWindow(WINDOW_NAME, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
    if (!window) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    return SDL_APP_CONTINUE;
}

static SDL_AppResult InitRenderer()
{
    SDL_PropertiesID props = SDL_CreateProperties();
    SDL_SetPointerProperty(props, SDL_PROP_RENDERER_CREATE_WINDOW_POINTER, window);

    renderer = SDL_CreateRendererWithProperties(props);
    SDL_DestroyProperties(props);

    if (renderer == NULL) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    if (!SDL_SetRenderVSync(renderer, 1)) {
        SDL_Log("Cannot activate VSync: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_SetRenderLogicalPresentation(renderer, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_LOGICAL_PRESENTATION_LETTERBOX);
    return SDL_APP_CONTINUE;
}

static SDL_AppResult InitTextEngine()
{
    if (!TTF_Init()) {
        SDL_Log("Failed to create text engine: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    font = TTF_OpenFont("ZenMaruGothic-Medium.ttf", font_size);
    if (!font) {
        SDL_Log("TTF_OpenFont Error: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    text_engine = TTF_CreateRendererTextEngine(renderer);
    text = TTF_CreateText(text_engine, font, "", 0);
    TTF_SetTextColor(text, 0, 0, 0, 255);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppInit([[maybe_unused]] void** appstate, [[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    if (!SDL_InitSubSystem(SDL_INIT_VIDEO)) {
        SDL_Log("SDL initialization failed: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (InitWindow() == SDL_APP_FAILURE
        || InitRenderer() == SDL_APP_FAILURE
        || InitTextEngine() == SDL_APP_FAILURE) {
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent([[maybe_unused]] void* appstate, SDL_Event* event)
{
    if (event->type == SDL_EVENT_QUIT) return SDL_APP_SUCCESS;

    if (event->type == SDL_EVENT_KEY_DOWN) {
        const int key = event->key.key;

        if (key == SDLK_ESCAPE) return SDL_APP_SUCCESS;

        if (key == SDLK_W) keys.w = true;
        if (key == SDLK_A) keys.a = true;
        if (key == SDLK_S) keys.s = true;
        if (key == SDLK_D) keys.d = true;

        if (key == SDLK_P && font) {
            font_size += 1.0f;
            TTF_SetFontSize(font, font_size);
        }
        if (key == SDLK_O && font) {
            font_size = SDL_max(1.0f, font_size - 1.0f);
            TTF_SetFontSize(font, font_size);
        }
    }

    if (event->type == SDL_EVENT_KEY_UP) {
        const int key = event->key.key;

        if (key == SDLK_W) keys.w = false;
        if (key == SDLK_A) keys.a = false;
        if (key == SDLK_S) keys.s = false;
        if (key == SDLK_D) keys.d = false;
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate([[maybe_unused]] void* appstate)
{
    if (keys.w) text_y -= MOVE_SPEED;
    if (keys.s) text_y += MOVE_SPEED;
    if (keys.a) text_x -= MOVE_SPEED;
    if (keys.d) text_x += MOVE_SPEED;

    const double now = ((double)SDL_GetTicks()) / 1000.0;
    const float red = (float)(0.5 + 0.5 * SDL_sin(now));
    const float green = (float)(0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 2 / 3));
    const float blue = (float)(0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 4 / 3));

    SDL_SetRenderDrawColorFloat(renderer, red, green, blue, SDL_ALPHA_OPAQUE_FLOAT);
    SDL_RenderClear(renderer);

    if (text) {
        const double rounded_now = std::round(now * 10.0) / 10.0;

        auto [ptr, ec] = std::to_chars(
            buffer, 
            buffer + sizeof(buffer),
            rounded_now,
            std::chars_format::fixed,
            1  // 1 decimal place
        );

        if (ec == std::errc()) {
            size_t length = ptr - buffer;
            TTF_SetTextString(text, buffer, length);
        }

        TTF_DrawRendererText(text, text_x, text_y);
    }

    SDL_RenderPresent(renderer);
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit([[maybe_unused]] void* appstate, [[maybe_unused]] SDL_AppResult result)
{
    TTF_DestroyText(text);
    TTF_DestroyRendererTextEngine(text_engine);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
}