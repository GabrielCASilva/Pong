#include "Ball.hpp"
#include "Constants.hpp"
#include <algorithm>
#include <raylib.h>

Ball::Ball(Vector2 position, float radius)
    : position(position), radius(radius), velocity({.x = 0, .y = 0}), direction({.x = 1, .y = 0})
{
}

void Ball::Loop(float deltaTime)
{
    const float acc{10.0F};
    acceleration = acc;
    velocity.x += acceleration * deltaTime * pong::PIXELS_PER_METTER * direction.x;
    velocity.y += acceleration * deltaTime * pong::PIXELS_PER_METTER * direction.y;

    const float max_vel{200.0F};
    velocity.x = std::clamp(velocity.x, -max_vel, max_vel);
    velocity.y = std::clamp(velocity.y, -max_vel, max_vel);

    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;

    ////// continue on screen
    const auto min_pos_x{static_cast<float>(pong::ball::RADIUS)};
    const auto max_pos_x{static_cast<float>(pong::WINDOW_WIDTH - pong::ball::RADIUS)};
    position.x = std::clamp(position.x, min_pos_x, max_pos_x);
    if (position.x >= max_pos_x || position.x <= min_pos_x)
    {
        direction.x *= -1;
        velocity.x *= -1;
    }

    const auto min_pos_y{static_cast<float>(pong::ball::RADIUS)};
    const auto max_pos_y{static_cast<float>(pong::WINDOW_HEIGHT - pong::ball::RADIUS)};
    position.y = std::clamp(position.y, min_pos_y, max_pos_y);
}

void Ball::Draw() const
{
    auto pos_x{static_cast<int>(position.x)};
    auto pos_y{static_cast<int>(position.y)};
    DrawCircle(pos_x, pos_y, radius, WHITE);
}

void Ball::StayOnScreen()
{
}
