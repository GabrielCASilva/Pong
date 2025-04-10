#include "ScreenManager.hpp"
#include "GameOverScreen.hpp"
#include "GameScreen.hpp"
#include "MenuScreen.hpp"
#include "ScreenType.hpp"
#include <memory>

auto ScreenManager::ChangeScreen(ScreenType new_type) -> void
{
    if (current_screen)
    {
        current_screen->Exit();
    }

    current_screen = CreateScreen(new_type);
    current_type = new_type;

    if (current_screen)
    {
        current_screen->Init();
    }
}

auto ScreenManager::Update(float delta_time) -> void
{
    if (current_screen)
    {
        current_screen->Update(delta_time);

        if (auto next = current_screen->NextScreen(); next.has_value())
        {
            ChangeScreen(next.value());
        }
    }
}

auto ScreenManager::Draw() const -> void
{
    if (current_screen)
    {
        current_screen->Draw();
    }
}

auto ScreenManager::CreateScreen(ScreenType type) -> std::unique_ptr<Screen>
{
    switch (type)
    {
    case ScreenType::GAME:
        return std::make_unique<GameScreen>();

    case ScreenType::MAIN_MENU:
        return std::make_unique<MenuScreen>();

    case ScreenType::GAME_OVER:
        return std::make_unique<GameOverScreen>();
    };

    return nullptr;
}
