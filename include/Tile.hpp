#pragma once

#include "GameObject.hpp"
#include "Collidable.hpp"
#include <SFML/Graphics.hpp>

class Tile : public GameObject,
             public Collidable
{
public:
    Tile();
    ~Tile() = default;
    void draw() const override;
    void applyCollision(Collidable& other) override;

protected:
    sf::FloatRect getBounds() const override;

private:
    sf::RectangleShape m_tile;
};