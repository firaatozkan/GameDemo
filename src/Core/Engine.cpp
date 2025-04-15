#include "Core/Engine.hpp"
#include "Core/Camera.hpp"
#include "Assets/Player.hpp"
#include "Assets/TileMap.hpp"
#include "Scenes/GameScene.hpp"

namespace Core
{
    Engine::Engine()
        : m_window(sf::VideoMode(static_cast<unsigned int>(Engine::GAME_WIDTH),
                                 static_cast<unsigned int>(Engine::GAME_HEIGHT)),
                   "Game Demo")
    {
        m_window.setFramerateLimit(60);
        m_window.setVerticalSyncEnabled(true);
    }

    Engine& Engine::get()
    {
        static Engine instance;
        return instance;
    }

    void Engine::run()
    {
        sf::Clock clock;

        m_scene = std::make_unique<Scenes::GameScene>();

        while (m_window.isOpen())
        {
            m_scene->handleEvents();

            const float deltaTime = clock.restart().asSeconds();
            m_scene->update(deltaTime);

            m_window.clear();
            m_scene->draw();
            m_window.display();
        }
    }

    sf::RenderWindow& Engine::renderer()
    {
        return m_window;
    }

    const sf::RenderWindow& Engine::renderer() const
    {
        return m_window;
    }

    void Engine::quit()
    {
        m_window.close();
    }
}