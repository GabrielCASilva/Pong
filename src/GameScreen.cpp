#include "GameScreen.hpp"
#include "Constants.hpp"
#include "Enemy.hpp"
#include "GameState.hpp"
#include "Player.hpp"
#include "Size.hpp"
#include "Visuals.hpp"
#include <cassert>
#include <cmath>
#include <iostream>
#include <memory>
#include <raylib.h>
#include <string>

auto GameScreen::Init() -> void
{
    Size size{.width = pong::paddle::WIDTH, .height = pong::paddle::HEIGHT};

    fx_ball = LoadSound("assets/pong.wav");

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
    const Vector2 ball_position{middle_width, middle_height};
    ball = std::make_unique<Ball>(ball_position, pong::ball::RADIUS);
}

auto GameScreen::Update(float delta_time, GameState &game_state) -> void
{
    if (game_over)
    {
        return;
    }

    if (init_timer)
    {
        if (timer >= 0)
        {
            timer -= delta_time;

            if (static_cast<float>(timer_r) >= timer)
            {
                brightness = max_brightness;
                timer_r = static_cast<int>(timer);
            }
            else
            {
                if (brightness > 0)
                {
                    brightness -= 5;
                }
            }
        }
        else
        {
            init_timer = false;
            timer = 3.0F;
            timer_r = 3;
        }

        return;
    }

    player->Loop(delta_time);

    ball->Loop(delta_time);
    ball->BounceOnPaddle(*player);
    if (ball->is_colliding_paddle)
    {
        PlaySound(fx_ball);
    }
    ball->BounceOnPaddle(*enemy);
    if (ball->is_colliding_paddle)
    {
        PlaySound(fx_ball);
    }
    ball->StayOnScreen();

    enemy->SetBall(ball.get());
    enemy->Loop(delta_time);

    if (ball->GetPosition().x <= -24)
    {
        enemy_points++;
        game_state.enemy_points = enemy_points;
        ball->SetDirection(Vector2{-1, 0});
        ball->Reset();
        player->Reset();
        enemy->Reset();
        init_timer = true;
    }

    if (ball->GetPosition().x >= pong::WINDOW_WIDTH + 24)
    {
        player_points++;
        game_state.player_points = player_points;
        ball->SetDirection(Vector2{1, 0});
        ball->Reset();
        player->Reset();
        enemy->Reset();
        init_timer = true;
    }

    if (!match_point && (player_points >= match_pointer_param || enemy_points >= match_pointer_param) &&
        (player_points == enemy_points))
    {
        match_point = true;
    }

    if (match_point)
    {
        ++winner_points;
        ++match_pointer_param;
        match_point = false;
    }

    if (player_points >= winner_points || enemy_points >= winner_points)
    {
        game_over = true;
        std::cout << "Partida acaba\n";

        if (player_points > enemy_points)
        {
            std::cout << "Player ganhou\n";
        }

        if (enemy_points > player_points)
        {
            std::cout << "Inimigo ganhou\n";
        }
    }
}

auto GameScreen::Draw() const -> void
{
    Visuals::GameBackground();
    std::string player_points_str{std::to_string(player_points)};
    DrawText(player_points_str.c_str(), (pong::WINDOW_WIDTH / 2) - 80, pong::MARGIN, 40, WHITE);

    std::string enemy_points_str{std::to_string(enemy_points)};
    DrawText(enemy_points_str.c_str(), (pong::WINDOW_WIDTH / 2) + 60, pong::MARGIN, 40, WHITE);

    player->Draw();
    enemy->Draw();
    ball->Draw();

    if (init_timer)
    {
        DrawRectangle(pong::WINDOW_WIDTH / 2 - 50, pong::WINDOW_HEIGHT / 2 - 155, 100, 100, DARKBLUE);

        auto timer_i{static_cast<int>(floor(timer))};
        std::string counter = timer_i > 0 ? std::to_string(timer_i) : "0";

        if (timer_i >= 0)
        {
            const int max_c{255};
            int width = MeasureText(counter.c_str(), 80);
            Color counter_color = (Color){max_c, max_c, max_c, static_cast<unsigned char>(brightness)};
            DrawText(counter.c_str(), pong::WINDOW_WIDTH / 2 - width / 2, pong::WINDOW_HEIGHT / 2 - 140, 80,
                     counter_color);
        }
    }
}

auto GameScreen::Exit() -> void
{
    UnloadSound(fx_ball); // Unload sound data
}

auto GameScreen::NextScreen() const -> std::optional<ScreenType>
{
    if (game_over)
    {
        return ScreenType::GAME_OVER;
    }
    return std::nullopt;
}
