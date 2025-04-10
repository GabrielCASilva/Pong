#ifndef GAME_OVER_SCREEN_HPP
#define GAME_OVER_SCREEN_HPP

#include "Screen.hpp"

class GameOverScreen : public Screen
{
  public:
    auto Init() -> void final;
    auto Update(float delta_time) -> void final;
    auto Draw() const -> void final;
    auto Exit() -> void final;

    [[nodiscard]] auto NextScreen() const -> std::optional<ScreenType> final;
};

#endif // !GAME_OVER_SCREEN_HPP
