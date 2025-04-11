#ifndef GAME_SCREEN_HPP
#define GAME_SCREEN_HPP

#include "Ball.hpp"
#include "Enemy.hpp"
#include "Player.hpp"
#include "Screen.hpp"
#include <memory>

class GameScreen : public Screen
{
  private:
    std::unique_ptr<Player> player;
    std::unique_ptr<Ball> ball;
    std::unique_ptr<Enemy> enemy;

    int player_points{};
    int enemy_points{};

  public:
    auto Init() -> void final;
    auto Update(float delta_time) -> void final;
    auto Draw() const -> void final;
    auto Exit() -> void final;

    [[nodiscard]] auto NextScreen() const -> std::optional<ScreenType> final;
};

#endif // !GAME_SCREEN_HPP
