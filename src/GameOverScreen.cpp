#include "GameOverScreen.hpp"
#include "Constants.hpp"
#include "GameState.hpp"
#include "ScreenType.hpp"
#include <iostream>
#include <optional>
#include <raylib.h>

auto GameOverScreen::Init() -> void
{
}

auto GameOverScreen::Update(float delta_time, GameState &game_state) -> void
{
    if (game_state.player_points > game_state.enemy_points)
    {
        std::cout << "Jogador ganhou\n";
    }
    else
    {
        std::cout << "Inimigo ganhou\n";
    }
}

auto GameOverScreen::Draw() const -> void
{
    DrawText("Game Over", pong::WINDOW_WIDTH / 2, pong::WINDOW_HEIGHT / 2, 20, WHITE);
}

auto GameOverScreen::Exit() -> void
{
}

auto GameOverScreen::NextScreen() const -> std::optional<ScreenType>
{
    return std::nullopt;
}
