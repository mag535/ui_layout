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
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);

    // create labels after initializing window so that rtext module is loaded.
    Text_Label label01 = Text_Label();
    Text_Label label02 = Text_Label(Vector2{ 100,100 }, 50, MAROON,
            "Hello, world", 10, LIME, 30, DARKBROWN);
    Text_Label label03 = Text_Label(Vector2{ 100,300 }, 30, DARKBLUE,
            "It works!", 10, SKYBLUE, 10, DARKBLUE);

    while (!WindowShouldClose()) {
        // update logic

        BeginDrawing();
            ClearBackground(RAYWHITE);
            // graphics
            label01.draw();
            label02.draw();
            label03.draw();
        EndDrawing();
    }

    CloseWindow();
}