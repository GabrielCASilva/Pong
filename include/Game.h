#pragma once

#include "Ball.h"
#include "Player.h"
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
    void Tick();

  private:
    void Draw() const;
    void Update();

    std::unique_ptr<Player> player;
    std::unique_ptr<Ball> ball;
};
