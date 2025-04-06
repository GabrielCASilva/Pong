#include "Ball.hpp"
#include "Constants.hpp"
#include "Paddle.hpp"
#include "Size.hpp"
#include <algorithm>
#include <cmath>
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
    const auto min_pos_x{static_cast<float>(pong::ball::RADIUS)};
    const auto max_pos_x{static_cast<float>(pong::WINDOW_WIDTH - pong::ball::RADIUS)};
    position.x = std::clamp(position.x, min_pos_x, max_pos_x);
    if (position.x >= max_pos_x || position.x <= min_pos_x)
    {
        direction.x *= -1;
        velocity.x *= -1;
        ChangeDirectionRandom();
    }

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

auto Ball::BouceOnPaddle(const Paddle &paddle, int sign) -> void
{
    Size p_size = paddle.getSize();
    Vector2 p_pos = paddle.getPosition();

    float _radius = radius * static_cast<float>(sign);
    bool collision_h1 = position.y + _radius >= p_pos.y;
    bool collision_h2 = position.y + _radius <= p_pos.y + static_cast<float>(p_size.height);
    bool collision_h = collision_h1 && collision_h2;

    bool collision_w1 = position.x + _radius >= p_pos.x;
    bool collision_w2 = position.x + _radius <= p_pos.x + static_cast<float>(p_size.width);
    bool collision_w = collision_w1 && collision_w2;

    if (collision_h && collision_w)
    {
        direction.x *= -1;
        velocity.x *= -1;

        // descobrindo onde a bola colidiu em relação ao eixo y
        float _p_height = static_cast<float>(p_size.height) / 2;
        float ball_collide = position.y - (p_pos.y + _p_height);

        // normaliza o valor para ver se ele bateu no centro, em cima ou em baixo
        float normalized = ball_collide / _p_height;
        normalized = std::clamp(normalized, -1.0F, 1.0F);

        const int RANGE = 31;
        const int _180 = 180;
        int random_number = (std::rand() % RANGE) + (RANGE - 1);
        float max_angle = static_cast<float>(random_number) * (PI / _180);
        float bounce_angle = normalized * max_angle;

        direction.x = std::cos(bounce_angle);
        direction.y = std::sin(bounce_angle);
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
