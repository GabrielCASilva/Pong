#include "Game.h"
#include "Constants.h"
#include "size.h"
#include <cassert>
#include <memory>
#include <raylib.h>

Game::Game(int width, int height, const std::string &title)
{
    assert(!GetWindowHandle());
    InitWindow(width, height, title.c_str());

    Size size{.width = pong::paddle::WIDTH, .height = pong::paddle::HEIGHT};
    const Vector2 player_pos{24, 24};
    paddle = std::make_unique<Paddle>(player_pos, size);
}

Game::~Game() noexcept
{
    assert(GetWindowHandle());
    CloseWindow();
}

auto Game::GameShouldClose() -> bool
{
    return WindowShouldClose();
}

void Game::Tick()
{
    Update();
    Draw();
}

void Game::Update()
{
    float delta_time = GetFrameTime();
    paddle->Loop(delta_time);
}

void Game::Draw()
{
    BeginDrawing();

    ClearBackground(BLACK);
    paddle->Draw();

    EndDrawing();
}
