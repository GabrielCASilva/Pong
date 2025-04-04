#pragma once

#include "size.h"
#include <raylib.h>
class Paddle
{
  public:
    Paddle(Vector2 position, Size size);

    void Loop(float deltaTime);
    void Draw() const;
    void StayOnScreen();

  private:
    Vector2 position;
    Size size;
    Vector2 velocity;
    float acceleration{0};

    void Integrate(float deltaTime);
};
