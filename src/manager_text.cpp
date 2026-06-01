#include "manager_text.h"
#include <stdexcept>
#include <algorithm>
#include <cctype>

using namespace manager;

bool TextManager::initialize(SDL_Renderer* renderer) 
{
    if (!TTF_Init()) return false;
    m_engine = TTF_CreateRendererTextEngine(renderer);
    return m_engine != nullptr;
}

TTF_Font* TextManager::load_font(const std::string& path, const std::string& key, float size)
{
    if (get_font_map()[path])
    {
        const char* err = "Font already exist";
        SDL_Log(err);
        throw std::runtime_error(err);
    }

    TTF_Font* font = TTF_OpenFont(path.c_str(), size);

    if (font == NULL)
    {
        SDL_Log("Font failed to load: %s", SDL_GetError());
        throw std::runtime_error("Font failed to load: " + path);
    }

    get_font_map()[key] = font;

    return font;
}

TTF_Font* TextManager::get_font(const std::string& key)
{
    TTF_Font* font = get_font_map()[key];

    if (!font)
        throw std::runtime_error("Font does not exist: " + key);

    return font;
}

void TextManager::shutdown()
{
    if (m_engine) TTF_DestroyRendererTextEngine(m_engine);

    TTF_Quit();
}