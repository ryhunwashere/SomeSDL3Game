#include "manager_text.h"

using namespace manager;

bool TextManager::initialize(SDL_Renderer* renderer) 
{
    if (!TTF_Init()) return false;
    m_engine = TTF_CreateRendererTextEngine(renderer);
    return m_engine != nullptr;
}

TTF_Font* TextManager::load_font(const std::string& path, float size) 
{
    return TTF_OpenFont(path.c_str(), size);
}

void TextManager::shutdown()
{
    if (m_engine) TTF_DestroyRendererTextEngine(m_engine);
    TTF_Quit();
}