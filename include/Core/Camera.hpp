#pragma once

#include <SFML/Graphics.hpp>

namespace Interfaces
{
    class Entity;
}

namespace Core
{
    class Camera
    {
    private:
        Camera();

    public:
        ~Camera() = default;
        static Camera& get();
        void update(const Interfaces::Entity& entity);

    private:
        sf::View m_view;
    };
}