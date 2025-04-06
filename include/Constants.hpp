#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

namespace pong
{
constexpr int WINDOW_WIDTH{800};
constexpr int WINDOW_HEIGHT{600};
constexpr int FPS{60};
constexpr int PIXELS_PER_METTER{100};
constexpr int MARGIN{24};

namespace paddle
{
constexpr int WIDTH{20};
constexpr int HEIGHT{100};
constexpr int ACC{20};
constexpr float MAX_VEL{300.0F};
} // namespace paddle

namespace ball
{
constexpr int RADIUS{8};
}
} // namespace pong
#endif // !CONSTANTS_HPP
