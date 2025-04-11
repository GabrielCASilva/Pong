#include "GameOverScreen.hpp"
#include "Constants.hpp"
#include "ScreenType.hpp"
#include <optional>
#include <raylib.h>

auto GameOverScreen::Init() -> void
{
}

auto GameOverScreen::Update(float delta_time) -> void
{
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
