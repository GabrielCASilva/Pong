#include "MenuScreen.hpp"
#include "Constants.hpp"
#include "GameState.hpp"
#include "ScreenType.hpp"
#include <optional>
#include <raylib.h>

auto MenuScreen::Init() -> void
{
}

auto MenuScreen::Update(float delta_time, GameState &game_state) -> void
{
    if (IsKeyPressed(KEY_ENTER))
    {
        start_game = true;
    }
}

auto MenuScreen::Draw() const -> void
{
    DrawText("MAIN MENU", (pong::WINDOW_WIDTH / 2) - 140, (pong::WINDOW_HEIGHT / 2) - 80, 50, WHITE);
    DrawText("Press enter to start", (pong::WINDOW_WIDTH / 2) - 160, (pong::WINDOW_HEIGHT / 2), 30, WHITE);
}

auto MenuScreen::Exit() -> void
{
}

auto MenuScreen::NextScreen() const -> std::optional<ScreenType>
{
    if (start_game)
    {
        return ScreenType::GAME;
    }
    return std::nullopt;
}
