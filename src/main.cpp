#include <iostream>
#include "raylib.h"

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

    while (!WindowShouldClose()) {
        // update logic

        BeginDrawing();
            ClearBackground(RAYWHITE);
            // graphics
        EndDrawing();
    }

    CloseWindow();
}