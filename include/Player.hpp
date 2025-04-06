#pragma once

#include "Paddle.hpp"
#include "size.hpp"
#include <raylib.h>

class Player : public Paddle
{
  public:
    Player(Vector2 position, Size size);
    auto moviment() -> float override;
};
