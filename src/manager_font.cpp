#include <stdexcept>
#include <algorithm>
#include <cctype>
#include "manager_font.h"

using namespace manager;

bool FontManager::init(SDL_Renderer* renderer)
{
    if (!TTF_Init()) return false;
    m_engine = TTF_CreateRendererTextEngine(renderer);
    return m_engine != nullptr;
}

TTF_Font* FontManager::loadFont(const std::string& path, const std::string& name, float size)
{
    if (m_fontMap[name])
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

    m_fontMap[name] = font;

    return font;
}

TTF_Font* FontManager::getFont(const std::string& name)
{
    TTF_Font* font = m_fontMap[name];

    if (!font)
        throw std::runtime_error("Font does not exist: " + name);

    return font;
}

void FontManager::shutdown()
{
    if (m_engine) TTF_DestroyRendererTextEngine(m_engine);

    TTF_Quit();
}