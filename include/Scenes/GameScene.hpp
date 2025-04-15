#pragma once

#include <memory>
#include <vector>
#include "Core/Camera.hpp"
#include "Assets/Player.hpp"
#include "Assets/TileMap.hpp"
#include "Interfaces/Scene.hpp"
#include "Interfaces/GameObject.hpp"

namespace Scenes
{
    class GameScene : public Interfaces::Scene
    {
    public:
        GameScene();

        ~GameScene() override = default;

        void handleEvents() override;

        void update(float dt) override;

        void draw() const override;

    private:
        void addObject(std::unique_ptr<Interfaces::GameObject> object);

        Core::Camera& m_cameraRef;
        Assets::Player* m_player {nullptr};
        std::vector<std::unique_ptr<Interfaces::GameObject>> m_objects;
        std::vector<std::reference_wrapper<Interfaces::CollidableObject>> m_collidableObjects;
        std::vector<std::reference_wrapper<Interfaces::Entity>> m_entities;
    };
}