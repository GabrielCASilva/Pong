#ifndef GAME_SCREEN_HPP
#define GAME_SCREEN_HPP

#include "Screen.hpp"

class GameScreen : public Screen
{
  public:
    auto Init() -> void final;
    auto Update(float delta_time) -> void final;
    auto Draw() const -> void final;
    auto Exit() -> void final;
};

#endif // !GAME_SCREEN_HPP
