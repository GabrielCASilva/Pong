#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Paddle.hpp"
#include "Size.hpp"
#include <raylib.h>

class Enemy : public Paddle
{
  public:
    Enemy(Vector2 position, Size size);
    auto moviment() -> float override;
};
#endif // !ENEMY_HPP
