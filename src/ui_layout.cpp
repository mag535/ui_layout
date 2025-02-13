#include "ui_layout.h"
#include "raylib.h"
#include <algorithm>
#include <iostream>


using namespace std;


/********** TEMPLATES *********************************************************/
template<>
Rectangle get_rectangle<Text_Label>(Text_Label& UIE)
{
    return (Rectangle){
            UIE.position.x,
            UIE.position.y,
            UIE.text_size.x + (2* (UIE.padding + UIE.border_width)),
            UIE.text_size.y + (2* (UIE.padding + UIE.border_width))
    };
}

template<>
Rectangle get_rectangle<Text_Input>(Text_Input& UIE)
{
    return (Rectangle){
            UIE.position.x,
            UIE.position.y,
            UIE.text_size.x + (2* (UIE.padding + UIE.border_width)),
            UIE.text_size.y + (2* (UIE.padding + UIE.border_width))
    };
}


/********** TEXT LABEL ********************************************************/
void create(Text_Label& TL)
{
    TL.text_size = MeasureTextEx(GetFontDefault(), TL.text.c_str(),
            (float)TL.font_size, (float)(TL.font_size/10));
    cout << TL.text_size.x << "," << TL.text_size.y << endl;
}

void draw(Text_Label& TL)
{
    // draw border
    if (TL.border_width != 0) {
        Vector2 size = Vector2{ 
                (float)(2*(TL.border_width + TL.padding) + TL.text_size.x),
                (float)(2*(TL.border_width + TL.padding) + TL.text_size.y) };
        DrawRectangleV(TL.position, size, TL.border_color);
    }
    // draw bg
    Vector2 pos = Vector2{ (float)(TL.position.x + TL.border_width),
            (float)(TL.position.y + TL.border_width) };
    Vector2 size = Vector2{ (float)(2*TL.padding + TL.text_size.x),
            (float)(2*TL.padding + TL.text_size.y) };
    if (TL.bg_color.a == 0)
        DrawRectangleV(pos, size, SCREEN_BG_COLOR);
    else
        DrawRectangleV(pos, size, TL.bg_color);
    // draw text
    if (!TL.text.empty()) {
        int pos_x = (int)TL.position.x + TL.border_width + TL.padding;
        int pos_y = (int)TL.position.y + TL.border_width + TL.padding;
        DrawText(TL.text.c_str(), pos_x, pos_y, TL.font_size, TL.font_color);
    }
}


/********** TEXT INPUT ********************************************************/
void create(Text_Input& TI)
{
    TI.text_size = MeasureTextEx(GetFontDefault(), "OOOOOOOOOO",
            (float)TI.font_size, (float)(TI.font_size/10));
    cout << TI.text_size.x << "," << TI.text_size.y << endl;
}

void read_user_input(Text_Input& TI)
{
    char c = GetCharPressed();
    while (c > 0) {
        if ((c >= 32) && (c <= 125) && (TI.text.length() < TI._char_limit))
            TI.text.append(1, c);
        c = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE) && (TI.text.length() > 0))
        TI.text.pop_back();
}

Color brighten_and_shift(const Color col)
{
    Color new_col;

    float brighten = 0.3;
    float shift = 0.5;
    Color dist = Color(
            255 - col.r,
            255 - col.g,
            255 - col.b
    );

    new_col = Color(
            (int)((float)col.r + (brighten * (float)dist.r)),
            (int)((float)col.g + (brighten * (float)dist.g)),
            (int)((float)col.b + (brighten * (float)dist.b)),
            255
    );

    if (new_col.r <= new_col.g && new_col.g <= new_col.b)
        new_col.g += (int)(shift * (float)(255 - new_col.g));
    else if (new_col.g <= new_col.b && new_col.b <= new_col.r)
        new_col.b += (int)(shift * (float)(255 - new_col.b));
    else if (new_col.b <= new_col.r && new_col.r <= new_col.g)
        new_col.r += (int)(shift * (float)(255 - new_col.r));

    return new_col;
}

Color invert_color(const Color col)
{
    return Color(
                255 - col.r,
                255 - col.g,
                255 - col.b,
                255
    );
}

void on_interaction(Text_Input& TI)
{
    switch (TI.state) {
    case NORMAL: {
        cout << "NORMAL" << endl;
        TI.current_color = TI.border_color;
        break; }
    case HOVER: {
        cout << "HOVER" << endl;
        TI.current_color = brighten_and_shift(TI.border_color);
        break; }
    case RESPONSIVE: {
        cout << "RESPONSIVE" << endl;
        TI.current_color = invert_color(TI.border_color);
        break; }
    case ACTIVE: {
        cout << "ACTIVE" << endl;
        TI.current_color = brighten_and_shift(TI.border_color);
        break; }
    default: {
        break; }
    }
}

void update(Text_Input& TI)
{
    if (CheckCollisionPointRec(GetMousePosition(), get_rectangle(TI))) {
        if (TI.state != ACTIVE && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            TI.state = RESPONSIVE;
        else if (TI.state != ACTIVE && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            TI.state = ACTIVE;
        else if (TI.state != ACTIVE)
            TI.state = HOVER;
    }else{
        if (TI.state == HOVER)
            TI.state = NORMAL;
        else if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            TI.state = NORMAL;
    }

    if (TI.state == ACTIVE) {
        read_user_input(TI);
        TI.frames_counter++;
    } else {
        TI.frames_counter = 0;
    }
    on_interaction(TI);
}

void draw(Text_Input& TI)
{
    // draw border
    if (TI.border_width != 0) {
        Vector2 size = Vector2{ 
                (float)(2*(TI.border_width + TI.padding) + TI.text_size.x),
                (float)(2*(TI.border_width + TI.padding) + TI.text_size.y) };
        DrawRectangleV(TI.position, size, TI.current_color);
    }
    // draw bg
    Vector2 pos = Vector2{ (float)(TI.position.x + TI.border_width),
            (float)(TI.position.y + TI.border_width) };
    Vector2 size = Vector2{ (float)(2*TI.padding + TI.text_size.x),
            (float)(2*TI.padding + TI.text_size.y) };
    if (TI.bg_color.a == 0)
        DrawRectangleV(pos, size, SCREEN_BG_COLOR);
    else
        DrawRectangleV(pos, size, TI.bg_color);
    // draw text
    if (!TI.text.empty()) {
        int pos_x = (int)TI.position.x + TI.border_width + TI.padding;
        int pos_y = (int)TI.position.y + TI.border_width + TI.padding;
        DrawText(TI.text.c_str(), pos_x, pos_y, TI.font_size, TI.font_color);
    }
    // draw cursor
    if (TI.state == ACTIVE) {
        if ((TI.frames_counter/20)%2 == 0) {
            DrawText("_",
                    (int)TI.position.x + 10 + MeasureText(TI.text.c_str(), TI.font_size),
                    TI.position.y + 14, TI.font_size, TI.font_color
            );
        }
    }
}




/*
Text_Input::Text_Input()
{
    m_position = Vector2{0, 0};
    m_font_size = 20;
    m_font_color = BLACK;
    m_text = "";
    m_padding = 5;
    m_bg_color = TRANSPARENT;
    m_border_width = 5;
    m_border_color = BLACK;
    m_state = NORMAL;

    _m_text_size = MeasureTextEx(GetFontDefault(), m_text.c_str(),
            (float)m_font_size, 0.0);
    
    _m_cursor_position = 0;
    _m_current_color = m_border_color;
    _m_frames_counter = 0;
}

Text_Input::Text_Input(Vector2 position, int font_size, Color font_color,
        int padding, Color bg_color, int border_width, Color border_color)
{
    m_position = position;
    m_font_size = font_size;
    m_font_color = font_color;
    m_text = "";
    m_padding = padding;
    m_bg_color = bg_color;
    if (border_width < 1)
        m_border_width = 1;
    else
        m_border_width = border_width;
    m_border_color = border_color;
    m_state = NORMAL;

    _m_text_size = MeasureTextEx(GetFontDefault(), "OOOOOOOOOO",
            (float)m_font_size, (float)(m_font_size/10));
    
    _m_cursor_position = 0;
    _m_current_color = border_color;
}

Rectangle Text_Input::get_rectangle()
{
    Rectangle rec = { m_position.x,
            m_position.y,
            _m_text_size.x + (2*(m_padding+m_border_width)),
            _m_text_size.y + (2*(m_padding+m_border_width)) };
    return rec;
}

void Text_Input::on_normal()
{
    _m_current_color = m_border_color;
}

void Text_Input::on_hover()
{
    Color dist = Color(255 - m_border_color.r,
            255 - m_border_color.g,
            255 - m_border_color.b);
    
    _m_current_color = Color(
            (int)((float)m_border_color.r + (0.2 * (float)dist.r)),
            (int)((float)m_border_color.g + (0.2 * (float)dist.g)),
            (int)((float)m_border_color.b + (0.2 * (float)dist.b))
    );
}

void Text_Input::on_response()
{
    _m_current_color = Color(255 - m_border_color.r,
            255 - m_border_color.g,
            255 - m_border_color.b);
}

void Text_Input::on_active()
{
    Color dist = Color(255 - m_border_color.r,
            255 - m_border_color.g,
            255 - m_border_color.b);
    
    _m_current_color = Color(m_border_color.r + (0.2 * dist.r),
            m_border_color.g + (0.2 * dist.g),
            m_border_color.b + (0.2 * dist.b));
}

void Text_Input::read_user_input()
{
    char c = GetCharPressed();
    while (c > 0) {
        if ((c >= 32) && (c <= 125) && (m_text.length() < _m_char_limit))
            m_text.append(1, c);
        c = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE) && (m_text.length() > 0))
        m_text.pop_back();
}

void Text_Input::update()
{
    if (m_state == ACTIVE) {
        read_user_input();
        _m_frames_counter++;
    } else {
        _m_frames_counter = 0;
    }

    // TODO: set the state
    // normal state
    if (!CheckCollisionPointRec(GetMousePosition(), get_rectangle()) &&
            IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        m_state = NORMAL;
        on_normal();
    // hover state
    } else if (CheckCollisionPointRec(GetMousePosition(), get_rectangle())) {
        m_state = HOVER;
        on_hover();
    // response state
    } else if (CheckCollisionPointRec(GetMousePosition(), get_rectangle()) &&
            IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        m_state = RESPONSIVE;
        on_response();
    // active state
    } else if (m_state == RESPONSIVE && IsMouseButtonUp(MOUSE_BUTTON_LEFT)) {
        m_state = ACTIVE;
        on_active();
    }
}

void Text_Input::draw()
{
    if (m_border_width != 0) {
        Vector2 size = Vector2{ 
                (float)(2*(m_border_width + m_padding) + _m_text_size.x),
                (float)(2*(m_border_width + m_padding) + _m_text_size.y) };
        DrawRectangleV(m_position, size, _m_current_color);
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
*/