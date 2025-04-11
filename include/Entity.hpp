#pragma once

#include "Collidable.hpp"
#include "GameObject.hpp"
#include <SFML/System.hpp>

class Entity : public GameObject,
               public Collidable
{
public:
    friend class Tile;

    explicit Entity(float mass);

    ~Entity() override = default;

    virtual void update(float deltaTime);

    void applyCollision(Collidable& other) override;

    void setGrounded();

    sf::Vector2f& getPosition();

    const sf::Vector2f& getPosition() const;

    sf::Vector2f& getVelocity();

    const sf::Vector2f& getVelocity() const;

protected:
    const float m_mass;
    bool m_isGrounded {false};
    sf::Vector2f m_position;
    sf::Vector2f m_velocity;
};