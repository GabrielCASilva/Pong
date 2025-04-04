#include <Paddle.h>
#include <algorithm>
#include <raylib.h>

Paddle::Paddle(Vector2 position, int width, int height)
    : position(position), width(width), height(height), velocity({.x = 0, .y = 0})
{
}

void Paddle::Loop(float deltaTime)
{
    int key_up = static_cast<int>(IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S));
    int key_down = static_cast<int>(IsKeyDown(KEY_UP) || IsKeyDown(KEY_W));
    acceleration = static_cast<float>(key_up - key_down);
    acceleration *= 10;
    Integrate(deltaTime);
}

void Paddle::Integrate(float deltaTime)
{
    velocity.y += acceleration * deltaTime * 100;
    if (acceleration == 0)
    {
        velocity.y *= 0.9F; // Reduz a velocidade gradativamente (ajuste o fator)
    }
    else
    {
        velocity.y = std::clamp(velocity.y, -200.0F, 200.0F);
    }
    position.y += velocity.y * deltaTime;
}

void Paddle::Draw() const
{
    DrawRectangle(position.x, position.y, width, height, WHITE);
}
