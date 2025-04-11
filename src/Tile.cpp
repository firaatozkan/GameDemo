#include <iostream>
#include "Tile.hpp"
#include "Entity.hpp"
#include "GameWindow.hpp"

Tile::Tile()
    : m_tile(sf::Vector2f(3000,
                          200))
{
    m_tile.setFillColor(sf::Color::Green);
    m_tile.setPosition(0, GameWindow::GAME_HEIGHT);
}

void Tile::draw() const
{
    GameWindow::get().getWindow().draw(m_tile);
}

sf::FloatRect Tile::getBounds() const
{
    return m_tile.getGlobalBounds();
}

void Tile::applyCollision(Collidable& other)
{
    auto entity = dynamic_cast<Entity*>(&other);
    if (entity)
    {
        auto& entityVelocity = entity->getVelocity();
        if (entityVelocity.y > 0)
        {
            entityVelocity.y = 0;
            entity->getPosition().y = getBounds().top - entity->getBounds().height;
            entity->setGrounded();
        }
    }
}
