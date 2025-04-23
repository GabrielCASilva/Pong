#ifndef VISUALS_HPP
#define VISUALS_HPP

#include <string>

class Visuals
{
  public:
    static auto GameBackground() -> void;
    static auto Text(std::string &text, int font_size, int pos_x, int pos_y) -> void;
    static auto TextBox(std::string &text, int font_size, int pos_x, int pos_y) -> void;
};

#endif // !VISUALS_HPP
