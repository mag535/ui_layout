#include <iostream>
#include "raylib.h"
#include "ui_layout.h"

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
    Text_Label tl00;
    Text_Label tl01 {
        { 200,0 },
        30,
        MAROON,
        "This is a text!!",
        10,
        SKYBLUE,
        5,
    };
    Text_Input ti00;
    Text_Input ti01 {
        { 50,300 },
        40,
        "help"
    };
    Text_Input ti02 {
        .position = { 50,400 },
        .font_size = 30,
        .numerical_only = true,
    };

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);

    // create labels after initializing window so that rtext module is loaded.
    create(tl00);
    create(tl01);
    create(ti00);
    create(ti01);
    ti01.state = DISABLED;
    create(ti02);

    while (!WindowShouldClose()) {
        // update logic
        update(ti00);
        update(ti01);
        update(ti02);

        BeginDrawing();
            ClearBackground(SCREEN_BG_COLOR);
            // graphics
            //draw(tl00);
            draw(tl01);
            draw(ti00);
            draw(ti01);
            draw(ti02);
        EndDrawing();
    }

    CloseWindow();
}