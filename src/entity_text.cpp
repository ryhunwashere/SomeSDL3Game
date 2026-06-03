#include <stdexcept>
#include <string>
#include "entity_text.h"
#include "manager_font.h"

using namespace entity;

bool TextEntity::create(TTF_Font* font, const std::string& initialText) 
{
    TTF_TextEngine* engine = manager::FontManager::get().getRawEngine();
    m_text = TTF_CreateText(engine, font, initialText.c_str(), initialText.length());

    return m_text != nullptr;
}

void TextEntity::updateText(const std::string& text)
{
    if (m_text)
        TTF_SetTextString(m_text, text.c_str(), text.length());
}

void TextEntity::setColor(float r, float g, float b, float a)
{
    if (m_text)
        TTF_SetTextColorFloat(m_text, r, g, b, a);
}

void TextEntity::setColor(float r, float g, float b)
{
    setColor(r, g, b, SDL_ALPHA_OPAQUE_FLOAT);
}

void TextEntity::setPosition(float x, float y)
{
    if (!m_text) return;

    m_x = x;
    m_y = y;
}

void TextEntity::move(float deltaX, float deltaY)
{
    if (!m_text) return;
    
    m_x += deltaX;
    m_y += deltaY;
}

void TextEntity::moveX(float deltaX)
{
    move(deltaX, 0.0f);
}

void TextEntity::moveY(float deltaY)
{
    move(0.0f, deltaY);
}

void TextEntity::draw()
{
    if (!m_text) return;

    if (!TTF_DrawRendererText(m_text, m_x, m_y))
    {
        SDL_Log(SDL_GetError());
        throw std::runtime_error(SDL_GetError());
    }
}

void TextEntity::destroy() 
{
    if (m_text) 
    {
        TTF_DestroyText(m_text);
        m_text = nullptr;
    }

    if (m_font) 
    {
        TTF_CloseFont(m_font);
        m_font = nullptr;
    }
}