#include "entity_text.h"
#include "manager_text.h"

using namespace entity;
using namespace manager;

bool TextEntity::create(TTF_Font* font, const std::string& initialText) 
{
    TTF_TextEngine* engine = TextManager::get().get_raw_engine();
    m_text_obj = TTF_CreateText(engine, font, initialText.c_str(), initialText.length());

    return m_text_obj != nullptr;
}

void TextEntity::update_text(const std::string& text) 
{
    if (m_text_obj)
        TTF_SetTextString(m_text_obj, text.c_str(), text.length());
}

void TextEntity::set_color_float(float r, float g, float b, float a)
{
    if (m_text_obj)
        TTF_SetTextColorFloat(m_text_obj, r, g, b, a);
}

void TextEntity::set_color_float(float r, float g, float b)
{
    TextEntity::set_color_float(r, g, b, SDL_ALPHA_OPAQUE_FLOAT);
}

void TextEntity::set_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    if (m_text_obj)
        TTF_SetTextColor(m_text_obj, r, g, b, a);
}

void TextEntity::set_color(Uint8 r, Uint8 g, Uint8 b)
{
    TextEntity::set_color(r, g, b, SDL_ALPHA_OPAQUE);
}

void TextEntity::draw(float x, float y) 
{
    if (m_text_obj)
        TTF_DrawRendererText(m_text_obj, x, y);
}

void TextEntity::destroy() 
{
    if (m_text_obj)
    {
        TTF_DestroyText(m_text_obj);
        m_text_obj = nullptr;
    }
}