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
    const int font_size = 60;
    int text_size = MeasureText(text.c_str(), font_size);
    int text_pos_x = (pong::WINDOW_WIDTH / 2) - (text_size / 2);
    int text_pos_y = (pong::WINDOW_HEIGHT / 2) - (font_size / 2);

    int rect_pos_x = text_pos_x - pong::MARGIN;
    int rect_pos_y = text_pos_y - pong::MARGIN;
    int rect_width = text_size + (pong::MARGIN * 2);
    int rect_heigh = font_size - 8 + (pong::MARGIN * 2);
    DrawRectangle(rect_pos_x, rect_pos_y, rect_width, rect_heigh, DARKBLUE);

    DrawText(text.c_str(), text_pos_x, text_pos_y, font_size, WHITE);
}

auto GameOverScreen::Exit() -> void
{
}

auto GameOverScreen::NextScreen() const -> std::optional<ScreenType>
{
    return std::nullopt;
}
