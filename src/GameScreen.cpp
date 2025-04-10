#include "GameScreen.hpp"
#include "Constants.hpp"
#include "Enemy.hpp"
#include "Player.hpp"
#include "Size.hpp"
#include <cassert>
#include <memory>
#include <raylib.h>

auto GameScreen::Init() -> void
{
    Size size{.width = pong::paddle::WIDTH, .height = pong::paddle::HEIGHT};

    // Player paddle
    auto middle_height = static_cast<float>(pong::WINDOW_HEIGHT) / 2;
    auto half_size_height = static_cast<float>(size.height) / 2;
    float paddle_height = middle_height - half_size_height;
    const Vector2 player_pos{pong::PADDLE_MARGIN, paddle_height};
    player = std::make_unique<Player>(player_pos, size);

    // Enemy paddle
    const Vector2 enemy_position{pong::WINDOW_WIDTH - pong::PADDLE_MARGIN - static_cast<float>(size.width),
                                 paddle_height};
    enemy = std::make_unique<Enemy>(enemy_position, size);

    // Ball
    auto middle_width{static_cast<float>(pong::WINDOW_WIDTH) / 2};
    const Vector2 ball_position{middle_width - pong::ball::RADIUS, middle_height};
    ball = std::make_unique<Ball>(ball_position, pong::ball::RADIUS);
}

auto GameScreen::Update(float delta_time) -> void
{
    player->Loop(delta_time);

    ball->Loop(delta_time);
    ball->BounceOnPaddle(*player);
    ball->BounceOnPaddle(*enemy);
    ball->StayOnScreen();

    enemy->SetBall(ball.get());
    enemy->Loop(delta_time);
}

auto GameScreen::Draw() const -> void
{
    player->Draw();
    enemy->Draw();
    ball->Draw();
}

auto GameScreen::Exit() -> void
{
}

auto GameScreen::NextScreen() const -> std::optional<ScreenType>
{
    return std::nullopt;
}
