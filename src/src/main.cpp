#include <iostream>
#include "raylib.h"
#include "../include/ui_layout.h"

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600
#define WINDOW_TITLE "UI Layout"

/*
 * Game Loop:
 *  1. Event Handling
 *  2. Updating Positions (and states)
 *  3. Drawing Objects
 */

int main(void)
{
    // setup logic
    Text_Label title {
        .position = { 20,0 },
        .font_size = 50,
        .font_color = DARKGREEN,
        .text = "My UI Library So Far:",
        .border_color = BLANK,
    };
    Text_Label subtitle {
        .position = { 50,60 },
        .font_size = 30,
        .font_color = DARKGREEN,
        .text = "Made with C(++) and RayLib!!",
        .bg_color = YELLOW,
        .border_color = DARKGREEN,
    };
    Text_Label label01 {
        .position = { 50,120 },
        .font_size = 30,
        .font_color = MAROON,
        .text = "This is a text label",
        .bg_color = YELLOW,
        .border_width = 10,
        .border_color = VIOLET,
    };
    Text_Input input01 {
        .position = { 20,200 },
        .font_size = 50,
        .font_color = MAROON,
        .bg_color = BEIGE,
        .border_color = MAROON,
    };
    Text_Input input02 {
        .position = { 20,300 },
        .font_size = 50,
        .font_color = MAROON,
        .bg_color = BEIGE,
        .border_color = MAROON,
        .numerical_only = true,
    };
    Button_Toggle toggle01 {
        .position = { 20,500 },
        .font_size = 30,
        .font_color = DARKBLUE,
        .bg_color = SKYBLUE,
        .border_color = DARKBLUE,
    };
    Button_Toggle toggle02 {
        .position = { 70,500 },
        .font_size = 30,
        .font_color = DARKBLUE,
        .bg_color = SKYBLUE,
        .border_color = DARKBLUE,
    };
    Button_Toggle toggle03 {
        .position = { 120,500 },
        .font_size = 30,
        .font_color = DARKBLUE,
        .bg_color = SKYBLUE,
        .border_color = DARKBLUE,
    };
    Button_Toggle toggle04 {
        .position = { 170,500 },
        .font_size = 30,
        .font_color = DARKBLUE,
        .bg_color = SKYBLUE,
        .border_color = DARKBLUE,
    };
    Button_Toggle toggle05 {
        .position = { 220,500 },
        .font_size = 30,
        .font_color = DARKBLUE,
        .bg_color = SKYBLUE,
        .border_color = DARKBLUE,
    };
    Text_Label lock {
        .position = { 320,500 },
        .font_size = 40,
        .font_color = DARKBLUE,
        .text = "LOCKED",
        .bg_color = SKYBLUE,
        .border_color = DARKBLUE,
    };

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);

    // create labels after initializing window so that rtext module is loaded.
    create(title);
    create(subtitle);
    create(label01);
    create(input01);
    create(input02);
    create(toggle01);
    create(toggle02);
    create(toggle03);
    create(toggle04);
    create(toggle05);
    create(lock);

    while (!WindowShouldClose()) {
        // update logic
        update(input01);
        update(input02);
        update(toggle01);
        update(toggle02);
        update(toggle03);
        update(toggle04);
        update(toggle05);

        // 10011
        if (toggle01.value && !toggle02.value && !toggle03.value &&
                toggle04.value && toggle05.value) {
            lock.text = "OPEN!!";
            lock.font_color = GOLD;
            lock.bg_color = YELLOW;
            lock.border_color = GOLD;
        }else{
            lock.text = "LOCKED";
            lock.font_color = DARKBLUE;
            lock.bg_color = SKYBLUE;
            lock.border_color = DARKBLUE;
        }

        BeginDrawing();
            ClearBackground(SCREEN_BG_COLOR);
            // graphics
            draw(title);
            draw(subtitle);
            draw(label01);
            draw(input01);
            draw(input02);
            draw(toggle01);
            draw(toggle02);
            draw(toggle03);
            draw(toggle04);
            draw(toggle05);
            draw(lock);
        EndDrawing();
    }

    CloseWindow();
}