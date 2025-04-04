#include "Constants.h"
#include "Game.h"
#include "raylib.h"

auto main() -> int
{
    Game game{pong::WINDOW_WIDTH, pong::WINDOW_HEIGHT, "Pong"};

    SetTargetFPS(pong::FPS);

    while (!Game::GameShouldClose())
    {
        game.Tick();
    }

    return 0;
}
