#pragma once

#include <SFML/Graphics.hpp>
#include "Interfaces/CollidableObject.hpp"

namespace Assets
{
    class TileMap : public Interfaces::CollidableObject
    {
    public:
        TileMap();
        ~TileMap() override = default;
        void draw() const override;
        void applyCollision(Interfaces::CollidableObject& other,
                            const sf::FloatRect& intersection) override;

    protected:
        sf::FloatRect getBounds() const override;

    private:
        sf::RectangleShape m_tileMap;
    };
}