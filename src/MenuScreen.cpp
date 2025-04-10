#include "MenuScreen.hpp"
#include "Constants.hpp"
#include "ScreenType.hpp"
#include <optional>
#include <raylib.h>

auto MenuScreen::Init() -> void
{
}

auto MenuScreen::Update(float delta_time) -> void
{
    if (IsKeyPressed(KEY_ENTER))
    {
        start_game = true;
    }
}

auto MenuScreen::Draw() const -> void
{
    DrawText("MenuScreen", (pong::WINDOW_WIDTH / 2) - 70, (pong::WINDOW_HEIGHT / 2) - 10, 20, WHITE);
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
