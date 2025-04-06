#pragma once

#include "Ball.hpp"
#include "Player.hpp"
#include <memory>
#include <string>

class Game
{
  public:
    Game(int width, int height, const std::string &title);
    Game(Game &&other) = delete;
    Game(const Game &other) = delete;
    ~Game() noexcept;
    auto operator=(Game &&other) -> Game & = delete;
    auto operator=(const Game &other) -> Game & = delete;

    [[nodiscard]] static auto GameShouldClose() -> bool;
    auto Tick() -> void;

  private:
    auto Draw() const -> void;
    auto Update() -> void;

    std::unique_ptr<Player> player;
    std::unique_ptr<Ball> ball;
};
