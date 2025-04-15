#include <iostream>
#include "Core/Engine.hpp"
#include "Assets/TileMap.hpp"
#include "Interfaces/Entity.hpp"

namespace Assets
{
    TileMap::TileMap()
        : m_tileMap(sf::Vector2f(3000,
                                 200))
    {
        m_tileMap.setFillColor(sf::Color::Green);
        m_tileMap.setPosition(0, Core::Engine::GAME_HEIGHT);
    }

    void TileMap::draw() const
    {
        Core::Engine::get().renderer().draw(m_tileMap);
    }

    sf::FloatRect TileMap::getBounds() const
    {
        return m_tileMap.getGlobalBounds();
    }

    void TileMap::applyCollision(Interfaces::CollidableObject& other,
                                 const sf::FloatRect& intersection)
    {
        auto entity = dynamic_cast<Interfaces::Entity*>(&other);
        if (entity)
        {
            auto& entityVelocity = entity->getVelocity();
            if (entityVelocity.y > 0)
            {
                entity->getPosition().y = getBounds().top - entity->getBounds().height;
                entity->setOnGround();
            }
        }
    }
}