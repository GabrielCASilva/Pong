#ifndef BALL_HPP
#define BALL_HPP

#include "Paddle.hpp"
#include <raylib.h>
class Ball
{
  public:
    Ball(Vector2 position, float radius);

    auto Loop(float deltaTime) -> void;
    auto Draw() const -> void;
    auto StayOnScreen() -> void;
    auto BounceOnPaddle(const Paddle &paddle) -> void;

  private:
    float acceleration{};
    Vector2 position;
    float radius;
    Vector2 velocity;
    Vector2 direction;

    auto Velocity(float deltaTime) -> void;
    auto Position(float deltaTime) -> void;
    static auto Clamp(Vector2 ball_v, float min_max) -> Vector2;
    static auto ClampMagnitude(Vector2 vec, float max_len) -> Vector2;

    auto ChangeDirectionRandom() -> void;
};
#endif // !BALL_HPP
