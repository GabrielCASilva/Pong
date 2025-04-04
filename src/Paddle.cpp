#include "Constants.h"
#include "size.h"
#include <Paddle.h>
#include <algorithm>
#include <raylib.h>

Paddle::Paddle(Vector2 position, Size size) : position(position), size(size), velocity({.x = 0, .y = 0})
{
}

void Paddle::Loop(float deltaTime)
{
    int key_up = static_cast<int>(IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S));
    int key_down = static_cast<int>(IsKeyDown(KEY_UP) || IsKeyDown(KEY_W));
    acceleration = static_cast<float>(key_up - key_down);
    acceleration *= pong::paddle::ACC;
    Integrate(deltaTime);
}

void Paddle::Integrate(float deltaTime)
{
    velocity.y += acceleration * deltaTime * pong::PIXELS_PER_METTER;
    if (acceleration == 0)
    {
        const float slow_velocity = 0.9F;
        velocity.y *= slow_velocity; // Reduz a velocidade gradativamente (ajuste o fator)
    }
    else
    {
        velocity.y = std::clamp(velocity.y, -pong::paddle::MAX_VEL, pong::paddle::MAX_VEL);
    }
    position.y += velocity.y * deltaTime;
}

void Paddle::Draw() const
{
    int pos_x = static_cast<int>(position.x);
    int pos_y = static_cast<int>(position.y);
    DrawRectangle(pos_x, pos_y, size.width, size.height, WHITE);
}
