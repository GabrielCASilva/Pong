#ifndef PADDLE_H
#define PADDLE_H

#include <raylib.h>
class Paddle
{
  public:
    Paddle(Vector2 position, int width, int height);

    void Loop(float deltaTime);
    void Draw() const;

  private:
    Vector2 position;
    int width;
    int height;
    Vector2 velocity;
    float acceleration{0};

    void Integrate(float deltaTime);
};

#endif // !PADDLE_H
