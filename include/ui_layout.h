#pragma once

#include "raylib.h"
#include <string>

#define SCREEN_BG_COLOR RAYWHITE
#define DISABLED_COLOR (Color){ 150,150,150,130 }


using namespace std;


template <typename T>
Rectangle get_rectangle(T& UIE);


enum interactive_state {
    NORMAL,
    HOVER,
    RESPONSIVE,
    ACTIVE,
    DISABLED
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
    
    Color _og_font_color = font_color;
    bool numerical_only = false;
};

void create(Text_Input& TI);
void read_user_input(Text_Input& TI);
Color brighten_and_shift(const Color col);
Color invert_color(const Color col);
void on_interaction(Text_Input& TI);
void update(Text_Input& TI);
void draw(Text_Input& TI);