#include "Game.h"
#include "raylib.h"

int main()
{
    Game game {};
    game.Init();
    game.Start();

    while (!WindowShouldClose())
    {
        game.Update();
        game.Draw();
    }

    game.Cleanup();
    return 0;
}