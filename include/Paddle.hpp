#ifndef PADDLE_HPP
#define PADDLE_HPP

#include "Size.hpp"
#include <raylib.h>
class Paddle
{
  public:
    Paddle(Vector2 position, Size size);

    Paddle(const Paddle &) = delete;                     // Construtor de cópia
    Paddle(Paddle &&) = delete;                          // Construtor de movimento
    auto operator=(const Paddle &) -> Paddle & = delete; // Atribuição por cópia
    auto operator=(Paddle &&) -> Paddle & = delete;      // Atribuição por movimento

    virtual ~Paddle() = default; // Destruidor virtual
    virtual auto Loop(float delta_time) -> void = 0;

    auto Draw() const -> void;
    auto StayOnScreen() -> void;

    [[nodiscard]] auto getSize() const -> Size;
    // [[nodiscard]] -> fala para o programador que, se ele não está usando o retorno, está usando o método
    // de maneira errada
    [[nodiscard]] auto getPosition() const -> Vector2;

  protected:
    Vector2 position;
    Size size;
    Vector2 velocity;
    float acceleration{0};

    auto Integrate(float deltaTime) -> void;
};
#endif // !PADDLE_HPP
