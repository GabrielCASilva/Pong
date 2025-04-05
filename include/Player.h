#pragma once

#include "Paddle.h"
#include "size.h"
#include <raylib.h>

class Player : public Paddle
{
  public:
    Player(Vector2 position, Size size);
    float moviment() override;
};
