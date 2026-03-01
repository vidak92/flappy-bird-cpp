#include <iostream>
#include "raylib.h"

int main()
{
    InitWindow(480, 720, "Flappy Bird");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(DARKGRAY);
        EndDrawing();
    }

    // @TODO cleanup

    return 0;
}