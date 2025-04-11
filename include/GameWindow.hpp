#pragma once

#include <SFML/Graphics.hpp>

class GameWindow
{
private:
    GameWindow();
    
public:
    static constexpr float GAME_WIDTH = 1280;
    static constexpr float GAME_HEIGHT = 720;

    static constexpr float WORLD_WIDTH = GAME_WIDTH * 5.f;
    static constexpr float WORLD_HEIGHT = GAME_HEIGHT * 1.2f;


    ~GameWindow() = default;

    static GameWindow& get();

    void run();

    sf::RenderWindow& getWindow();

    const sf::RenderWindow& getWindow() const;

private:
    sf::RenderWindow m_window;
};
