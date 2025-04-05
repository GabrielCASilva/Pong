#include "Ball.h"
#include <raylib.h>

Ball::Ball(Vector2 position, float radius) : position(position), radius(radius), velocity({.x = 0, .y = 0})
{
}

void Ball::Loop()
{
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
