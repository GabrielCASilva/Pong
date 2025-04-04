#include "Game.h"
#include <cassert>
#include <memory>
#include <raylib.h>

Game::Game(int width, int height, const std::string &title)
{
    assert(!GetWindowHandle());
    InitWindow(width, height, title.c_str());
    paddle = std::make_unique<Paddle>(Vector2{24, 24}, 20, 100);
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
    float dt = GetFrameTime();
    paddle->Loop(dt);
}

void Game::Draw()
{
    BeginDrawing();

    ClearBackground(BLACK);
    paddle->Draw();

    EndDrawing();
}
