#pragma once

#include <SFML/Graphics.hpp>

class Entity;

class Camera
{
private:
    Camera();

public:
    ~Camera() = default;
    static Camera& get();
    void update(const Entity& entity);

private:
    sf::View m_view;
};