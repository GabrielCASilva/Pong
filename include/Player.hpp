#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Paddle.hpp"
#include "Size.hpp"
#include <raylib.h>

class Player : public Paddle
{
  public:
    Player(Vector2 position, Size size);
    auto Loop(float delta_time) -> void override;
};
#endif // !PLAYER_HPP
