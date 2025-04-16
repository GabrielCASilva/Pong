#include "Visuals.hpp"
#include "Constants.hpp"
#include <raylib.h>

auto Visuals::GameBackground() -> void
{
    DrawRectangle((pong::WINDOW_WIDTH / 2) - 5, 0, 10, pong::WINDOW_HEIGHT, DARKBLUE);
    DrawRectangleLinesEx(Rectangle{0, 0, pong::WINDOW_WIDTH, pong::WINDOW_HEIGHT}, 10, DARKBLUE);
}
