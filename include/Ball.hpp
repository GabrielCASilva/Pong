#pragma once

#include <raylib.h>
class Ball
{
  public:
    Ball(Vector2 position, float radius);

    void Loop(float deltaTime);
    void Draw() const;
    void StayOnScreen();

  private:
    float acceleration{0};
    Vector2 position;
    float radius;
    Vector2 velocity;
    Vector2 direction;
};
