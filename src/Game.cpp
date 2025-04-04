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

    // Player paddle
    float middle_height = static_cast<float>(pong::WINDOW_HEIGHT) / 2;
    float half_size_height = static_cast<float>(size.height) / 2;
    float paddle_height = middle_height - half_size_height;
    const Vector2 player_pos{24, paddle_height};
    paddle = std::make_unique<Paddle>(player_pos, size);

    // TODO: Enemy paddle
    // TODO: Ball
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
