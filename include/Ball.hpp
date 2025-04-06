#ifndef BALL_HPP
#define BALL_HPP

#include <raylib.h>
class Ball
{
  public:
    Ball(Vector2 position, float radius);

    auto Loop(float deltaTime) -> void;
    auto Draw() const -> void;
    auto StayOnScreen() -> void;

  private:
    float acceleration{0};
    Vector2 position;
    float radius;
    Vector2 velocity;
    Vector2 direction;
};
#endif // !BALL_HPP
