#include "Interfaces/CollidableObject.hpp"

namespace Interfaces
{
    void CollidableObject::resolveCollision(CollidableObject& other)
    {
        sf::FloatRect intersection;
        if (getBounds().intersects(other.getBounds(), intersection))
        {
            applyCollision(other, intersection);
            other.applyCollision(*this, intersection);
        }
    }
}