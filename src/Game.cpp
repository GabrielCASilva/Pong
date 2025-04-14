#include "Game.hpp"
#include "ScreenManager.hpp"
#include "ScreenType.hpp"
#include <cassert>
#include <memory>
#include <raylib.h>

Game::Game(int width, int height, const std::string &title)
{
    assert(!GetWindowHandle());
    InitWindow(width, height, title.c_str());
    screen_manager = std::make_unique<ScreenManager>();
    screen_manager->ChangeScreen(ScreenType::GAME);
}

Game::~Game() noexcept
{
    assert(GetWindowHandle());
    CloseWindow();
}

auto Game::GameShouldClose() -> bool
{
    return WindowShouldClose();
}

auto Game::Tick() -> void
{
    Update();
    Draw();
}

auto Game::Update() -> void
{
    float delta_time = GetFrameTime();
    screen_manager->Update(delta_time, game_state);
}

auto Game::Draw() const -> void
{
    BeginDrawing();
    ClearBackground(BLACK);
    screen_manager->Draw();
    EndDrawing();
}
