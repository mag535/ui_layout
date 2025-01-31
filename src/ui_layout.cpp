#include "ui_layout.h"
#include "raylib.h"
#include <iostream>


Text_Label::Text_Label()
{
    m_position = Vector2{0, 0};
    m_font_size = 20;
    m_font_color = BLACK;
    m_text = "...";
    m_padding = 5;
    m_bg_color = TRANSPARENT;
    m_border_width = 0;
    m_border_color = BLACK;

    _m_text_size = MeasureTextEx(GetFontDefault(), m_text.c_str(),
            (float)m_font_size, 0.0);
}

Text_Label::Text_Label(Vector2 position, int font_size, Color font_color,
        string text, int padding, Color bg_color, int border_width,
        Color border_color)
{
    m_position = position;
    m_font_size = font_size;
    m_font_color = font_color;
    m_text = text;
    m_padding = padding;
    m_bg_color = bg_color;
    m_border_width = border_width;
    m_border_color = border_color;

    _m_text_size = MeasureTextEx(GetFontDefault(), m_text.c_str(),
            (float)m_font_size, (float)(m_font_size/10));
}

void Text_Label::draw()
{
    if (m_border_width != 0) {
        Vector2 size = Vector2{ 
                (float)(2*(m_border_width + m_padding) + _m_text_size.x),
                (float)(2*(m_border_width + m_padding) + _m_text_size.y) };
        DrawRectangleV(m_position, size, m_border_color);
    }
    if (m_bg_color.a != 0) {
        Vector2 pos = Vector2{ (float)(m_position.x + m_border_width),
                (float)(m_position.y + m_border_width) };
        Vector2 size = Vector2{ (float)(2*m_padding + _m_text_size.x),
                (float)(2*m_padding + _m_text_size.y) };
        DrawRectangleV(pos, size, m_bg_color);
    }
    if (!m_text.empty()) {
        int pos_x = (int)m_position.x + m_border_width + m_padding;
        int pos_y = (int)m_position.y + m_border_width + m_padding;
        DrawText(m_text.c_str(), pos_x, pos_y, m_font_size, m_font_color);
    }
}