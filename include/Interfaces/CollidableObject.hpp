#pragma once

#include <SFML/Graphics.hpp>
#include "GameObject.hpp"

namespace Interfaces
{
    class CollidableObject : public GameObject
    {
    public:
        ~CollidableObject() override = default;
        void resolveCollision(CollidableObject& other);

    protected:
        virtual sf::FloatRect getBounds() const = 0;
        virtual void applyCollision(CollidableObject& other, const sf::FloatRect& intersection) = 0;
    };
}