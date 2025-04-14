#ifndef GAME_HPP
#define GAME_HPP

#include "GameState.hpp"
#include "ScreenManager.hpp"
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

    GameState game_state{};
    std::unique_ptr<ScreenManager> screen_manager;
};
#endif // !GAME_HPP
