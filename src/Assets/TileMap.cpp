#include <array>
#include <cassert>
#include <iostream>
#include "Assets/TileMap.hpp"
#include "Interfaces/Entity.hpp"

namespace Assets
{
    TileMap::TileMap()
        : m_tiles(sf::Quads, TILE_COUNT * 1 * 4)
    {
        const bool loaded = m_tileTexture.loadFromFile(ASSETS_DIR "Tileset.png");
        assert(loaded);

        const auto tileIndices = TileMap::generateIndices();

        const unsigned int tilesPerRow = m_tileTexture.getSize().x / TILE_SIZE;

        for (auto x = 0; x < tileIndices.size(); ++x)
        {
            const unsigned int groundTile = tileIndices[x];
            const unsigned int tu = groundTile % tilesPerRow;
            const unsigned int tv = groundTile / tilesPerRow;

            sf::Vertex* const quad = &m_tiles[x * 4];

            // Position (y = 5 for the ground row)
            quad[0].position = sf::Vector2f(static_cast<float>(x * TILE_SIZE),
                                            static_cast<float>(((Core::Engine::WORLD_HEIGHT / TILE_SIZE) - 1) * TILE_SIZE));

            quad[1].position = sf::Vector2f(static_cast<float>((x + 1) * TILE_SIZE),
                                            static_cast<float>(((Core::Engine::WORLD_HEIGHT / TILE_SIZE) - 1) * TILE_SIZE));

            quad[2].position = sf::Vector2f(static_cast<float>((x + 1) * TILE_SIZE),
                                            static_cast<float>(Core::Engine::WORLD_HEIGHT));

            quad[3].position = sf::Vector2f(static_cast<float>(x * TILE_SIZE),
                                            static_cast<float>(Core::Engine::WORLD_HEIGHT));

            // Texture coordinates
            quad[0].texCoords = sf::Vector2f(static_cast<float>(tu * TILE_SIZE),
                                             static_cast<float>(tv * TILE_SIZE));

            quad[1].texCoords = sf::Vector2f(static_cast<float>((tu + 1) * TILE_SIZE),
                                             static_cast<float>(tv * TILE_SIZE));

            quad[2].texCoords = sf::Vector2f(static_cast<float>((tu + 1) * TILE_SIZE),
                                             static_cast<float>((tv + 1) * TILE_SIZE));

            quad[3].texCoords = sf::Vector2f(static_cast<float>(tu * TILE_SIZE),
                                             static_cast<float>((tv + 1) * TILE_SIZE));
        }

        m_renderState.texture = &m_tileTexture;
    }

    void TileMap::draw() const
    {
        Core::Engine::get().renderer().draw(m_tiles, m_renderState);
    }

    sf::FloatRect TileMap::getBounds() const
    {
        return {-static_cast<float>(TILE_SIZE),
                m_tiles[0].position.y,
                static_cast<float>(Core::Engine::WORLD_WIDTH + TILE_SIZE),
                static_cast<float>(TILE_SIZE)};
    }

    void TileMap::applyCollision(Interfaces::CollidableObject &other,
                                 const sf::FloatRect &intersection)
    {
        auto entity = dynamic_cast<Interfaces::Entity *>(&other);
        if (entity)
        {
            auto &entityVelocity = entity->getVelocity();
            if (entityVelocity.y > 0)
            {
                entity->getPosition().y = getBounds().top - entity->getBounds().height;
                entity->setOnGround();
            }
        }
    }

    constexpr std::array<unsigned int, TileMap::TILE_COUNT> TileMap::generateIndices()
    {
        std::array<unsigned int, TILE_COUNT> tileIndices;
        tileIndices.fill(1);
        tileIndices.front() = 0;
        tileIndices.back() = 5;

        return tileIndices;
    }
}