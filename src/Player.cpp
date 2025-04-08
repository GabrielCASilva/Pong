#include "Player.hpp"
#include "Constants.hpp"

Player::Player(Vector2 position, Size size) : Paddle(position, size)
{
}

auto Player::Loop(float delta_time) -> void
{
    int key_up{static_cast<int>(IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))};
    int key_down{static_cast<int>(IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))};
    acceleration = static_cast<float>(key_up - key_down);
    acceleration *= pong::paddle::ACC;
    Integrate(delta_time);
    StayOnScreen();
}
