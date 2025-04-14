#ifndef MENU_SCREEN_HPP
#define MENU_SCREEN_HPP

#include "Screen.hpp"

class MenuScreen : public Screen
{
  private:
    bool start_game{false};

  public:
    auto Init() -> void final;
    auto Update(float delta_time, GameState &game_state) -> void final;
    auto Draw() const -> void final;
    auto Exit() -> void final;

    [[nodiscard]] auto NextScreen() const -> std::optional<ScreenType> final;
};

#endif // !MENU_SCREEN_HPP
