#include "Player.h"

Player::Player(Vector2 position, Size size) : Paddle(position, size)
{
}

float Player::moviment()
{
    int key_up = static_cast<int>(IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S));
    int key_down = static_cast<int>(IsKeyDown(KEY_UP) || IsKeyDown(KEY_W));
    return static_cast<float>(key_up - key_down);
}
