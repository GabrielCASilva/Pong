#pragma once

#include "size.hpp"
#include <raylib.h>
class Paddle
{
  public:
    Paddle(Vector2 position, Size size);

    Paddle(const Paddle &) = delete;            // Construtor de cópia
    Paddle(Paddle &&) = delete;                 // Construtor de movimento
    Paddle &operator=(const Paddle &) = delete; // Atribuição por cópia
    Paddle &operator=(Paddle &&) = delete;      // Atribuição por movimento

    virtual ~Paddle() = default; // Destruidor virtual
    virtual float moviment() = 0;

    void Loop(float deltaTime);
    void Draw() const;
    void StayOnScreen();

  private:
    Vector2 position;
    Size size;
    Vector2 velocity;
    float acceleration{0};

    void Integrate(float deltaTime);
};
