#pragma once

#include "raylib.h"
#include <string>

#define TRANSPARENT (Color){ 0, 0, 0, 0 }


using namespace std;


class Text_Label
{
    Vector2 m_position;
    int m_font_size;
    Color m_font_color;
    string m_text;
    int m_padding;
    Color m_bg_color;
    int m_border_width;
    Color m_border_color;

    Vector2 _m_text_size;

public:
    Text_Label();
    Text_Label(Vector2 position, int font_size, Color font_color, string text,
        int padding, Color bg_color, int border_width, Color border_color);

    void draw();
};