#pragma once

#include "Paddle.h"
#include <memory>
#include <string>

class Game
{
  public:
    Game(int width, int height, const std::string &title);
    Game(Game &&other) = delete;
    auto operator=(Game &&other) -> Game & = delete;
    Game(const Game &other) = delete;
    auto operator=(const Game &other) -> Game & = delete;
    ~Game() noexcept;

    [[nodiscard]] static auto GameShouldClose() -> bool;
    void Tick();

  private:
    void Draw();
    void Update();

    std::unique_ptr<Paddle> paddle;
};
