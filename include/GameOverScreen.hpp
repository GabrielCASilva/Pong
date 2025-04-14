#ifndef GAME_OVER_SCREEN_HPP
#define GAME_OVER_SCREEN_HPP

#include "Screen.hpp"
#include <string>

class GameOverScreen : public Screen
{
  private:
    bool is_winner{false};
    static auto Message(std::string &text) -> void;

  public:
    auto Init() -> void final;
    auto Update(float delta_time, GameState &game_state) -> void final;
    auto Draw() const -> void final;
    auto Exit() -> void final;

    [[nodiscard]] auto NextScreen() const -> std::optional<ScreenType> final;
};

#endif // !GAME_OVER_SCREEN_HPP
