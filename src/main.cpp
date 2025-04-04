#include "Constants.h"
#include "Game.h"
#include "raylib.h"

int main()
{
    Game game{pong::WINDOW_WIDTH, pong::WINDOW_HEIGHT, "Pong"};

    SetTargetFPS(60);

    while (!game.GameShouldClose())
    {
        game.Tick();
    }

    return 0;
}
