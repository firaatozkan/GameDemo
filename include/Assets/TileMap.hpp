#pragma once

#include <SFML/Graphics.hpp>
#include "Core/Engine.hpp"
#include "Interfaces/CollidableObject.hpp"

namespace Assets
{
    class TileMap : public Interfaces::CollidableObject
    {
    public:
        static constexpr unsigned int TILE_COUNT = static_cast<unsigned int>(Core::Engine::WORLD_WIDTH / 64.f);
        static constexpr unsigned int TILE_SIZE = 64;

        TileMap();
        ~TileMap() override = default;
        void draw() const override;
        void applyCollision(Interfaces::CollidableObject& other,
                            const sf::FloatRect& intersection) override;

    protected:
        sf::FloatRect getBounds() const override;

    private:
        static constexpr std::array<unsigned int, TILE_COUNT> generateIndices();

        sf::Texture m_tileTexture;
        sf::VertexArray m_tiles;
        sf::RenderStates m_renderState;
    };
}