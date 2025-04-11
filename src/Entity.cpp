#include <iostream>
#include "Tile.hpp"
#include "Entity.hpp"

Entity::Entity(float mass)
    : m_mass(mass)
{
}

void Entity::update(float deltaTime)
{
    m_velocity.y = m_isGrounded ? 0 : (m_velocity.y + deltaTime * 9.81f * m_mass);
    m_position += m_velocity * deltaTime;
    m_isGrounded = false;
}

void Entity::applyCollision(Collidable &other)
{
    const sf::FloatRect selfBounds = getBounds();
    const sf::FloatRect otherBounds = other.getBounds();

    if (!selfBounds.intersects(otherBounds))
        return;

    sf::FloatRect intersection;
    selfBounds.intersects(otherBounds, intersection);

    if (intersection.width < intersection.height)
    {
        // Resolve in X axis
        if (selfBounds.left < otherBounds.left)
            m_position.x -= intersection.width;
        else
            m_position.x += intersection.width;

        m_velocity.x = 0;
    }
    else
    {
        // Resolve in Y axis
        if (selfBounds.top < otherBounds.top)
            m_position.y -= intersection.height;
        else
            m_position.y += intersection.height;

        m_velocity.y = 0;

        if (selfBounds.top < otherBounds.top)
            setGrounded(); // You landed on something
    }
}

void Entity::setGrounded()
{
    m_isGrounded = true;
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