#include "Constants.hpp"
#include "Game.hpp"
#include "raylib.h"

auto main() -> int
{
    InitAudioDevice();
    Game game{pong::WINDOW_WIDTH, pong::WINDOW_HEIGHT, "Pong"};

    SetTargetFPS(pong::FPS);

    while (!Game::GameShouldClose())
    {
        game.Tick();
    }
    CloseAudioDevice();
    return 0;
}
