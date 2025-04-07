#include "Enemy.hpp"

Enemy::Enemy(Vector2 position, Size size) : Paddle(position, size)
{
}

auto Enemy::moviment() -> float
{
    return 0;
}
