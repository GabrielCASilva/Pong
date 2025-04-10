#include "Enemy.hpp"
#include "Ball.hpp"
#include "Constants.hpp"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <raylib.h>

Enemy::Enemy(Vector2 position, Size size) : Paddle(position, size)
{
}

auto Enemy::Loop(float delta_time) -> void
{
    if (ball != nullptr)
    {
        // ball info
        Vector2 b_pos{ball->GetPosition()};
        Vector2 b_vel{ball->GetVelocity()};

        // prevendo a posição da bola no próximo frame
        const float prediction_time{delta_time};
        float b_future_pos_y{b_pos.y + (b_vel.y * prediction_time)};

        // paddle center position
        auto width{static_cast<float>(pong::paddle::WIDTH)};
        auto height{static_cast<float>(pong::paddle::HEIGHT)};
        Vector2 center_pos{Vector2{position.x + (width / 2), position.y + (height / 2)}};

        float dist_y{b_future_pos_y - center_pos.y};
        const float dead_zone = static_cast<float>(pong::paddle::HEIGHT) / 3;
        if (std::abs(dist_y) < dead_zone)
        {
            acceleration = 0;
        }
        else
        {
            float middle_width = static_cast<float>(pong::WINDOW_WIDTH) / 2;
            if (b_vel.x > 0)
            {
                const int inpult_dist{200};
                if (std::abs(dist_y) > inpult_dist)
                {
                    acceleration = (dist_y > 0 ? 1.0F : -1.0F) * pong::paddle::ACC;
                }
                else
                {
                    const float max_distance = middle_width;
                    float clamped = std::clamp(std::abs(dist_y) / max_distance, 0.0F, 1.0F);
                    float desired_acc = (dist_y > 0 ? 1.0F : -1.0F) * clamped * pong::paddle::ACC;

                    // Faz a transição suave da aceleração anterior pra nova
                    acceleration = std::lerp(previous_acceleration, desired_acc, 0.3F);

                    // Salva a aceleração atual pra usar no próximo frame
                    previous_acceleration = acceleration;
                }
            }
            else
            {
                acceleration = 0;
            }
        }
    }
    else
    {
        acceleration = 0;
    }

    Integrate(delta_time);
    StayOnScreen();
}

auto Enemy::SetBall(const Ball *ball) -> void
{
    this->ball = ball;
}
