#include "GameOverScreen.hpp"
#include "Constants.hpp"
#include "GameState.hpp"
#include "ScreenType.hpp"
#include "Visuals.hpp"
#include <optional>
#include <raylib.h>
#include <string>

auto GameOverScreen::Init() -> void
{
}

auto GameOverScreen::Update(float delta_time, GameState &game_state) -> void
{
    if (game_state.player_points > game_state.enemy_points)
    {
        is_winner = true;
    }

    if (IsKeyPressed(KEY_ENTER))
    {
        go_to_game = true;
    }
}

auto GameOverScreen::Draw() const -> void
{
    Visuals::GameBackground();
    std::string text{};
    if (is_winner)
    {
        text = "YOU WIN";
    }
    else
    {
        text = "YOU LOSE";
    }

    Message(text);
}

auto GameOverScreen::Message(std::string &text) -> void
{
    const int font_size_1{60};
    Visuals::TextBox(text, font_size_1, pong::WINDOW_WIDTH / 2, pong::WINDOW_HEIGHT / 2);

    std::string text_press_enter{"Press enter to return"};
    const int font_size_2{20};
    Visuals::Text(text_press_enter, font_size_2, pong::WINDOW_WIDTH - 150, pong::WINDOW_HEIGHT - 30);
}

auto GameOverScreen::Exit() -> void
{
}

auto GameOverScreen::NextScreen() const -> std::optional<ScreenType>
{
    if (go_to_game)
    {
        return ScreenType::GAME;
    }
    return std::nullopt;
}
