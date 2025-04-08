#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Ball.hpp"
#include "Constants.hpp"
#include "Paddle.hpp"
#include "Size.hpp"
#include <raylib.h>

class Enemy : public Paddle
{
  private:
    const Ball *ball{nullptr};
    float previous_acceleration{};
    float acc{pong::paddle::ACC};

  public:
    Enemy(Vector2 position, Size size);
    auto Loop(float delta_time) -> void override;
    auto SetBall(const Ball *ball) -> void;
};
#endif // !ENEMY_HPP
