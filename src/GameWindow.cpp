#include "GameWindow.hpp"
#include "Tile.hpp"
#include "Player.hpp"
#include "Camera.hpp"

GameWindow::GameWindow()
    : m_window(sf::VideoMode(static_cast<unsigned int>(GameWindow::GAME_WIDTH),
                             static_cast<unsigned int>(GameWindow::GAME_HEIGHT)),
               "Game Demo")
{
    m_window.setFramerateLimit(60);
    m_window.setVerticalSyncEnabled(true);
}

GameWindow& GameWindow::get()
{
    static GameWindow instance;
    return instance;
}

void GameWindow::run()
{
    sf::Clock clock;

    Tile tile;
    Player player;
    auto& camera = Camera::get();

    while (m_window.isOpen())
    {
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                m_window.close();
            else
                player.handleInputs(event);
        }

        if (tile.isColliding(player))
            tile.applyCollision(player);

        const float deltaTime = clock.restart().asSeconds();
        player.update(deltaTime);
        camera.update(player);
        
        m_window.clear();
        tile.draw();
        player.draw();
        m_window.display();
    }
}

sf::RenderWindow& GameWindow::getWindow()
{
    return m_window;
}

const sf::RenderWindow& GameWindow::getWindow() const
{
    return m_window;
}
