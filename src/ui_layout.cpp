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
        TI.font_color = TI._og_font_color;
        break; }
    case HOVER: {
        cout << "HOVER" << endl;
        TI.current_color = brighten_and_shift(TI.border_color);
        TI.font_color = TI._og_font_color;
        break; }
    case RESPONSIVE: {
        cout << "RESPONSIVE" << endl;
        TI.current_color = invert_color(TI.border_color);
        TI.font_color = TI._og_font_color;
        break; }
    case ACTIVE: {
        cout << "ACTIVE" << endl;
        TI.current_color = brighten_and_shift(TI.border_color);
        TI.font_color = TI._og_font_color;
        break; }
    case DISABLED: {
        cout << "DISABLED" << endl;
        TI.current_color = DISABLED_COLOR;
        TI.font_color = DISABLED_COLOR;
        break; }
    default: {
        break; }
    }
}

void update(Text_Input& TI)
{
    if (TI.state == DISABLED)
        goto on_disabled_exit;

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

on_disabled_exit:
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
    // draw char counter
    string limit_display = to_string(TI.text.length()) + "/" + to_string(TI._char_limit);
    int _font_size = 10;
    if (TI.font_size/2 > _font_size)
        _font_size = TI.font_size/2;
    Vector2 limit_size = MeasureTextEx(GetFontDefault(),
            limit_display.c_str(),
            (float)_font_size,
            (float)_font_size/10
    );
    int pos_x = TI.position.x + TI.text_size.x + (2 * (TI.padding + TI.border_width)) - limit_size.x;
    int pos_y = TI.position.y + TI.text_size.y + (2 * (TI.padding + TI.border_width)) + 5;
    DrawText(limit_display.c_str(), pos_x, pos_y, _font_size, TI.font_color);
}