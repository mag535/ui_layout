#pragma once

#include "raylib.h"
#include <string>

#define SCREEN_BG_COLOR RAYWHITE


using namespace std;


template <typename T>
Rectangle get_rectangle(T& UIE);


enum interactive_state {
    NORMAL,
    HOVER,
    RESPONSIVE,
    ACTIVE
};


struct Text_Label
{
    Vector2 position { 0,0 };
    int font_size = 20;
    Color font_color = BLACK;
    string text = "Hello, World!";
    int padding = 5;
    Color bg_color = BLANK;
    int border_width = 3;
    Color border_color = BLACK;
    Vector2 text_size { 0,0 };
};

void create(Text_Label& TL);
void draw(Text_Label& TL);


struct Text_Input
{
    Vector2 position { 0,0 };
    int font_size = 20;
    string text = "";
    Color font_color = DARKBLUE;
    int padding = 5;
    Color bg_color = BLANK;
    int border_width = 5;
    Color border_color = DARKBLUE;
    Vector2 text_size { 0,0 };
    enum interactive_state state = NORMAL;

    const unsigned int _char_limit = 10;
    int frames_counter = 0;
    int cursor_position = 0;
    Color current_color = DARKBLUE;
};

void create(Text_Input& TI);
void read_user_input(Text_Input& TI);
Color brighten_and_shift(const Color col);
Color invert_color(const Color col);
void on_interaction(Text_Input& TI);
void update(Text_Input& TI);
void draw(Text_Input& TI);


/*
class Text_Input
{
    Vector2 m_position;
    int m_font_size;
    string m_text;
    Color m_font_color;
    int m_padding;
    Color m_bg_color;
    int m_border_width;
    Color m_border_color;

    const unsigned int _m_char_limit = 10;

    int _m_frames_counter;
    int _m_cursor_position;
    Vector2 _m_text_size;
    Color _m_current_color;
    enum interactive_state m_state;
    
    // normal state color is border color
    // hovering state color is brighter version of normal state
    // pre-activation state color inverts normal state color
    // active state color is same as hovering state color

public:
    Text_Input();
    Text_Input(Vector2 position, int font_size, Color font_color, int padding,
            Color bg_color, int border_width, Color border_color);
    Rectangle get_rectangle();

    void on_normal();
    void on_hover();
    void on_response();
    void on_active();

    void read_user_input();

    void update();
    void draw();
};
*/