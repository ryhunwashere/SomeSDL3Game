#include "entity_text.h"
#include "manager_text.h"
#include <stdexcept>
#include <string>

bool entity::TextEntity::create(TTF_Font* font, const std::string& initialText) 
{
    TTF_TextEngine* engine = manager::TextManager::get().get_raw_engine();
    m_text_obj = TTF_CreateText(engine, font, initialText.c_str(), initialText.length());

    return m_text_obj != nullptr;
}

void entity::TextEntity::update_text(const std::string& text)
{
    if (m_text_obj)
        TTF_SetTextString(m_text_obj, text.c_str(), text.length());
}

void entity::TextEntity::set_color_float(float r, float g, float b, float a)
{
    if (m_text_obj)
        TTF_SetTextColorFloat(m_text_obj, r, g, b, a);
}

void entity::TextEntity::set_color_float(float r, float g, float b)
{
    TextEntity::set_color_float(r, g, b, SDL_ALPHA_OPAQUE_FLOAT);
}

void entity::TextEntity::set_position(float x, float y)
{
    if (m_text_obj)
    {
        m_pos_x = x;
        m_pos_y = y;
    }
}

void entity::TextEntity::move(float x, float y)
{
    if (m_text_obj)
    {
        m_pos_x += x;
        m_pos_y += y;
    }
}

void entity::TextEntity::draw()
{
    if (m_text_obj)
    {
        if (!TTF_DrawRendererText(m_text_obj, m_pos_x, m_pos_y))
        {
            SDL_Log(SDL_GetError());
            throw std::runtime_error(SDL_GetError());
        }
    }
}

void entity::TextEntity::destroy()
{
    if (m_text_obj)
    {
        TTF_DestroyText(m_text_obj);
        m_text_obj = nullptr;
    }
}