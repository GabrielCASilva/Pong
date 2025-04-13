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

    int timer_r{3};
    float timer{3.0F};
    bool init_timer{false};

    // IU
    const int max_brightness{255};
    int brightness{max_brightness};

    // Condição para fim de jogo
    int match_pointer_param{2};
    int winner_points{3};
    bool match_point{false};
    bool game_over{false};

  public:
    auto Init() -> void final;
    auto Update(float delta_time) -> void final;
    auto Draw() const -> void final;
    auto Exit() -> void final;

    [[nodiscard]] auto NextScreen() const -> std::optional<ScreenType> final;
};

#endif // !GAME_SCREEN_HPP
