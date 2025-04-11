#pragma once

#include <SFML/Graphics.hpp>

class Entity;

class Collidable
{
public:
    friend class Entity;

    virtual ~Collidable() = default;
    virtual void applyCollision(Collidable& other) = 0;
    
    bool isColliding(const Collidable& other) const
    {
        return getBounds().intersects(other.getBounds());
    }
    
protected:
    virtual sf::FloatRect getBounds() const = 0;
};
