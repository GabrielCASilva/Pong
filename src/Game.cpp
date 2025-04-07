#include "Game.hpp"
#include "Constants.hpp"
#include "Enemy.hpp"
#include "Player.hpp"
#include "Size.hpp"
#include <cassert>
#include <memory>
#include <raylib.h>

Game::Game(int width, int height, const std::string &title)
{
    assert(!GetWindowHandle());
    InitWindow(width, height, title.c_str());

    Size size{.width = pong::paddle::WIDTH, .height = pong::paddle::HEIGHT};

    // Player paddle
    auto middle_height = static_cast<float>(pong::WINDOW_HEIGHT) / 2;
    auto half_size_height = static_cast<float>(size.height) / 2;
    float paddle_height = middle_height - half_size_height;
    const Vector2 player_pos{pong::PADDLE_MARGIN, paddle_height};
    player = std::make_unique<Player>(player_pos, size);

    // TODO: Enemy paddle
    Size _size{.width = pong::paddle::WIDTH, .height = pong::paddle::HEIGHT * 2};
    float _paddle_height = middle_height - (static_cast<float>(_size.height) / 2);
    const Vector2 enemy_position{pong::WINDOW_WIDTH - (pong::PADDLE_MARGIN * 4), _paddle_height};
    enemy = std::make_unique<Enemy>(enemy_position, _size);

    // Ball
    auto middle_width{static_cast<float>(pong::WINDOW_WIDTH) / 2};
    const Vector2 ball_position{middle_width - pong::ball::RADIUS, middle_height};
    ball = std::make_unique<Ball>(ball_position, pong::ball::RADIUS);
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

auto Game::Tick() -> void
{
    Update();
    Draw();
}

auto Game::Update() -> void
{
    float delta_time = GetFrameTime();
    player->Loop(delta_time);
    ball->Loop(delta_time);
    ball->BounceOnPaddle(*player);
    ball->BounceOnPaddle(*enemy);
    ball->StayOnScreen();
}

auto Game::Draw() const -> void
{
    BeginDrawing();

    ClearBackground(BLACK);

    player->Draw();
    enemy->Draw();
    ball->Draw();

    EndDrawing();
}
