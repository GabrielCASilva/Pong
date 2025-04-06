#include "Paddle.hpp"
#include "Constants.hpp"
#include "Size.hpp"
#include <algorithm>
#include <raylib.h>

Paddle::Paddle(Vector2 position, Size size) : position(position), size(size), velocity({.x = 0, .y = 0})
{
}

auto Paddle::Loop(float deltaTime) -> void
{
    acceleration = moviment();
    acceleration *= pong::paddle::ACC;
    Integrate(deltaTime);
    StayOnScreen();
}

auto Paddle::StayOnScreen() -> void
{
    auto sup_margin = static_cast<float>(pong::MARGIN);
    auto inf_margin = static_cast<float>(pong::WINDOW_HEIGHT - pong::MARGIN - size.height);
    position.y = std::clamp(position.y, sup_margin, inf_margin);
    if (position.y == sup_margin || position.y == inf_margin)
    {
        velocity.y = 0;
    }
}

auto Paddle::Integrate(float deltaTime) -> void
{
    velocity.y += acceleration * deltaTime * pong::PIXELS_PER_METTER;
    if (acceleration == 0)
    {
        const float slow_velocity{0.9F};
        velocity.y *= slow_velocity;
        const float min_threshold{0.1F};
        if (std::abs(velocity.y) < min_threshold)
        {
            velocity.y = 0;
        }
    }
    else
    {
        velocity.y = std::clamp(velocity.y, -pong::paddle::MAX_VEL, pong::paddle::MAX_VEL);
    }
    position.y += velocity.y * deltaTime;
}

auto Paddle::Draw() const -> void
{
    auto pos_x = static_cast<int>(position.x);
    auto pos_y = static_cast<int>(position.y);
    DrawRectangle(pos_x, pos_y, size.width, size.height, WHITE);
}
