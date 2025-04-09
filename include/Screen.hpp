#ifndef SCREEN_HPP
#define SCREEN_HPP

class Screen
{
  public:
    Screen() = default;
    virtual ~Screen() = default;

    Screen(const Screen &) = delete;                     // Construtor de cópia
    Screen(Screen &&) = delete;                          // Construtor de movimento
    auto operator=(const Screen &) -> Screen & = delete; // Atribuição por cópia
    auto operator=(Screen &&) -> Screen & = delete;      // Atribuição por movimento

    virtual auto Init() -> void = 0;
    virtual auto Update(float delta_time) -> void = 0;
    virtual auto Draw() const -> void = 0;
    virtual auto Exit() -> void = 0;
};

#endif // !SCREEN_HPP
