#include "Ball.hpp"
#include "Constants.hpp"
#include "Paddle.hpp"
#include "Size.hpp"
#include <algorithm>
#include <cmath>
#include <cstdarg>
#include <cstdlib>
#include <raylib.h>

Ball::Ball(Vector2 position, float radius)
    : position(position), radius(radius), velocity({.x = 0, .y = 0}), direction({.x = -1, .y = 0})
{
}

auto Ball::Loop(float deltaTime) -> void
{

    const float max_acc = 20.F;
    acceleration = max_acc;

    Velocity(deltaTime);

    const float max_vel{500.0F};
    velocity = ClampMagnitude(velocity, max_vel);
    Position(deltaTime);
}

auto Ball::Draw() const -> void
{
    auto pos_x{static_cast<int>(position.x)};
    auto pos_y{static_cast<int>(position.y)};
    DrawCircle(pos_x, pos_y, radius, WHITE);
}

auto Ball::StayOnScreen() -> void
{
    /*
      const auto min_pos_x{static_cast<float>(pong::ball::RADIUS)};
      const auto max_pos_x{static_cast<float>(pong::WINDOW_WIDTH - pong::ball::RADIUS)};
      position.x = std::clamp(position.x, min_pos_x, max_pos_x);
      if (position.x >= max_pos_x || position.x <= min_pos_x)
      {
          direction.x *= -1;
          velocity.x *= -1;
          ChangeDirectionRandom();
      }
  */
    const auto min_pos_y{static_cast<float>(pong::ball::RADIUS + pong::MARGIN)};
    const auto max_pos_y{static_cast<float>(pong::WINDOW_HEIGHT - pong::ball::RADIUS - pong::MARGIN)};
    position.y = std::clamp(position.y, min_pos_y, max_pos_y);
    if (position.y >= max_pos_y || position.y <= min_pos_y)
    {
        direction.y *= -1;
        velocity.y *= -1;
        ChangeDirectionRandom();
    }
}

auto Ball::ChangeDirectionRandom() -> void
{
    const int RANGE = 31;
    int random_number = (std::rand() % RANGE) - (RANGE / 2);

    float angle = std::atan2(direction.y, direction.x);

    const int _180 = 180;
    angle += static_cast<float>(random_number) * (PI / _180);

    direction.x = std::cos(angle);
    direction.y = std::sin(angle);
}

auto Ball::BounceOnPaddle(const Paddle &paddle) -> void
{
    // get paddle position / size
    Vector2 paddle_position{paddle.getPosition()};
    Size paddle_size{paddle.getSize()};

    // alinha a posicao para o meio do paddle
    auto p_width{static_cast<float>(paddle_size.width)};
    auto p_height{static_cast<float>(paddle_size.height)};
    Vector2 paddle_position_middle{Vector2{paddle_position.x + (p_width / 2), paddle_position.y + (p_height / 2)}};

    Vector2 distance_paddle_ball{Vector2{0, 0}};
    if (position.x >= paddle_position_middle.x)
    {
        // distancia = bola - paddle
        distance_paddle_ball.x = (position.x - radius) - (paddle_position_middle.x + (p_width / 2));
    }
    else
    {
        // distancia = paddle - bola
        distance_paddle_ball.x = (paddle_position_middle.x - (p_width / 2)) - (position.x + radius);
    }

    if (position.y >= paddle_position_middle.y)
    {
        // distancia = bola - paddle
        distance_paddle_ball.y = (position.y - radius) - (paddle_position_middle.y + (p_height / 2));
    }
    else
    {
        // distancia = paddle - bola
        distance_paddle_ball.y = (paddle_position_middle.y - (p_height / 2)) - (position.y + radius);
    }

    // Colidiu! Bola com Paddle
    if (distance_paddle_ball.x < 0 && distance_paddle_ball.y < 0)
    {
        float overlap_left = (position.x + radius) - (paddle_position_middle.x - (p_width / 2));
        float overlap_right = (paddle_position_middle.x + (p_width / 2)) - (position.x - radius);
        float overlap_top = (position.y + radius) - (paddle_position_middle.y - (p_height / 2));
        float overlap_bottom = (paddle_position_middle.y + (p_height / 2)) - (position.y - radius);

        float min_overlap_x = std::min(overlap_left, overlap_right);
        float min_overlap_y = std::min(overlap_top, overlap_bottom);

        if (min_overlap_x < min_overlap_y)
        {
            // corrigindo a posicao da bola
            if (overlap_left < overlap_right)
            {
                position.x -= overlap_left - 1;
            }
            else
            {
                position.x += overlap_right + 1;
            }

            direction.x *= -1;
            velocity.x *= -1;
            ChangeDirectionRandom();
        }
        else
        {
            // corrigindo a posicao da bola
            if (overlap_top < overlap_bottom)
            {
                position.y -= overlap_top - 1;
            }
            else
            {
                position.y += overlap_bottom + 1;
            }

            direction.y *= -1;
            velocity.y *= -1;
            ChangeDirectionRandom();
        }
    }
}

auto Ball::Clamp(Vector2 ball_v, float min_max) -> Vector2
{
    ball_v.x = std::clamp(ball_v.x, -min_max, min_max);
    ball_v.y = std::clamp(ball_v.y, -min_max, min_max);
    return ball_v;
}

auto Ball::ClampMagnitude(Vector2 vec, float max_len) -> Vector2
{
    float mag_squared = (vec.x * vec.x) + (vec.y * vec.y);
    if (mag_squared > max_len * max_len)
    {
        float mag = std::sqrt(mag_squared);
        vec.x = vec.x / mag * max_len;
        vec.y = vec.y / mag * max_len;
    }
    return vec;
}

auto Ball::Reset() -> void
{
    auto middle_height = static_cast<float>(pong::WINDOW_HEIGHT) / 2;
    auto middle_width{static_cast<float>(pong::WINDOW_WIDTH) / 2};
    position = Vector2{middle_width - pong::ball::RADIUS, middle_height};
    velocity = Vector2{0, 0};
}

auto Ball::SetDirection(Vector2 direction) -> void
{
    this->direction = direction;
}

auto Ball::Velocity(float deltaTime) -> void
{
    velocity.x += acceleration * deltaTime * pong::PIXELS_PER_METTER * direction.x;
    velocity.y += acceleration * deltaTime * pong::PIXELS_PER_METTER * direction.y;
}

auto Ball::Position(float deltaTime) -> void
{
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
}

auto Ball::GetVelocity() const -> Vector2
{
    return velocity;
}

auto Ball::GetPosition() const -> Vector2
{
    return position;
}
