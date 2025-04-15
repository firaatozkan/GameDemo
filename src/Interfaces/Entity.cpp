#include <iostream>
#include "Assets/TileMap.hpp"
#include "Interfaces/Entity.hpp"

namespace Interfaces
{
    Entity::Entity(float mass)
        : m_mass(mass)
    {
    }

    void Entity::updateVelocity(float deltaTime)
    {
        m_velocity.y += deltaTime * 9.81f * m_mass;
    }

    void Entity::applyCollision(CollidableObject& other,
                                const sf::FloatRect& intersection)
    {
        // auto entity = dynamic_cast<Entity*>(&other);
        // if (entity)
        // {
        //     auto& entityVelocity = entity->getVelocity();
        //     if (entityVelocity.y > 0)
        //     {
        //         entityVelocity.y = 0;
        //         entity->getPosition().y = getBounds().top - entity->getBounds().height;
        //         entity->setGrounded();
        //     }
        // }
    }

    void Entity::updateAnimation(float deltaTime)
    {
        m_animator.update(deltaTime);

        runAnimationLogic();
    }

    void Entity::updatePosition(float deltaTime)
    {
        m_position += m_velocity * deltaTime;
    }

    void Entity::draw() const
    {
        m_animator.draw(m_position, m_flipped);
    }

    void Entity::setOnGround()
    {
        m_velocity.y = 0;
        m_onGround = true;
    }

    sf::Vector2f& Entity::getPosition()
    {
        return m_position;
    }

    const sf::Vector2f& Entity::getPosition() const
    {
        return m_position;
    }

    sf::Vector2f& Entity::getVelocity()
    {
        return m_velocity;
    }

    const sf::Vector2f& Entity::getVelocity() const
    {
        return m_velocity;
    }
}