#include "Visuals.hpp"
#include "Constants.hpp"
#include <raylib.h>
#include <string>

auto Visuals::GameBackground() -> void
{
    DrawRectangle((pong::WINDOW_WIDTH / 2) - 5, 0, 10, pong::WINDOW_HEIGHT, DARKBLUE);
    DrawRectangleLinesEx(Rectangle{0, 0, pong::WINDOW_WIDTH, pong::WINDOW_HEIGHT}, 10, DARKBLUE);
}

auto Visuals::Text(std::string &text, int font_size, int pos_x, int pos_y) -> void
{
    int text_size = MeasureText(text.c_str(), font_size);
    int text_pos_x = pos_x - (text_size / 2);
    int text_pos_y = pos_y - (font_size / 2);
    DrawText(text.c_str(), text_pos_x, text_pos_y, font_size, WHITE);
}

auto Visuals::TextBox(std::string &text, int font_size, int pos_x, int pos_y) -> void
{

    int text_size = MeasureText(text.c_str(), font_size);
    int text_pos_x = pos_x - (text_size / 2);
    int text_pos_y = pos_y - (font_size / 2);

    int rect_pos_x = text_pos_x - pong::MARGIN;
    int rect_pos_y = text_pos_y - pong::MARGIN;
    int rect_width = text_size + (pong::MARGIN * 2);
    int rect_heigh = font_size - 8 + (pong::MARGIN * 2);
    DrawRectangle(rect_pos_x, rect_pos_y, rect_width, rect_heigh, DARKBLUE);

    Visuals::Text(text, font_size, pos_x, pos_y);
}
