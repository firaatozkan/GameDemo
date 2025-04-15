#pragma once

#include <SFML/Graphics.hpp>
#include "Interfaces/Scene.hpp"

namespace Core
{
    class Engine
    {
    private:
        Engine();

    public:
        static constexpr float GAME_WIDTH = 1280;
        static constexpr float GAME_HEIGHT = 720;

        static constexpr float WORLD_WIDTH = GAME_WIDTH * 5.f;
        static constexpr float WORLD_HEIGHT = GAME_HEIGHT * 1.2f;

        ~Engine() = default;

        static Engine& get();

        void run();

        sf::RenderWindow& renderer();

        const sf::RenderWindow& renderer() const;

        void quit();

    private:
        sf::RenderWindow m_window;
        std::unique_ptr<Interfaces::Scene> m_scene;
    };
}