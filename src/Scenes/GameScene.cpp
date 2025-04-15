#include <SFML/Graphics.hpp>
#include "Core/Engine.hpp"
#include "Scenes/GameScene.hpp"

namespace Scenes
{
    GameScene::GameScene()
        : m_cameraRef(Core::Camera::get())
    {
        addObject(std::make_unique<Assets::Player>());
        addObject(std::make_unique<Assets::TileMap>());
    }

    void GameScene::handleEvents()
    {
        auto& renderer = Core::Engine::get().renderer();
        sf::Event event;
        while (renderer.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                Core::Engine::get().quit();
                break;
            }
            else
                m_player->handleInputs(event);
        }
    }

    void GameScene::update(float dt)
    {
        for (Interfaces::Entity& entity : m_entities)
            entity.updateVelocity(dt);

        for (size_t i = 0; i < m_collidableObjects.size(); ++i)
        {
            for (size_t j = i + 1; j < m_collidableObjects.size(); ++j)
            {
                Interfaces::CollidableObject& first = m_collidableObjects[i];
                Interfaces::CollidableObject& second = m_collidableObjects[j];
                first.resolveCollision(second);
            }
        }

        for (Interfaces::Entity& entity : m_entities)
            entity.updatePosition(dt);

        for (Interfaces::Entity& entity : m_entities)
            entity.updateAnimation(dt);

        m_cameraRef.update(*m_player);
    }

    sf::Color GameScene::getBackgroundColor() const
    {
        return {100, 149, 237};
    }

    void GameScene::draw() const
    {
        for (const auto& object : m_objects)
            object->draw();
    }

    void GameScene::addObject(std::unique_ptr<Interfaces::GameObject> object)
    {
        auto collidable = dynamic_cast<Interfaces::CollidableObject*>(object.get());
        if (collidable)
            m_collidableObjects.emplace_back(*collidable);

        auto entity = dynamic_cast<Interfaces::Entity*>(collidable);
        if (entity)
            m_entities.emplace_back(*entity);

        auto player = dynamic_cast<Assets::Player*>(entity);
        if (player)
            m_player = player;

        m_objects.emplace_back(std::move(object));
    }
}