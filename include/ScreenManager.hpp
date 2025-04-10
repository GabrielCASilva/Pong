#ifndef SCREEN_MANAGER_HPP
#define SCREEN_MANAGER_HPP

#include "Screen.hpp"
#include "ScreenType.hpp"
#include <memory>

class ScreenManager
{
  public:
    auto ChangeScreen(ScreenType new_type) -> void;
    auto Update(float delta_time) -> void;
    auto Draw() const -> void;

  private:
    std::unique_ptr<Screen> current_screen;
    ScreenType current_type;
    static auto CreateScreen(ScreenType type) -> std::unique_ptr<Screen>;
};

#endif // !SCREEN_MANAGER_HPP
