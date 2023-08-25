#pragma once

#include <vector>
#include "ECS/Entity.hpp"
#include "ECS/GenericSystem.hpp"

union SDL_Event;
struct SDL_Renderer;

class World
{
public:
    World() = default;
    ~World() = default;
    void handleInput(const SDL_Event& event);
    void updateWorld(unsigned int deltaTime);
    void renderWorld();
    Entity& createEntity();

    RenderSystem& getRenderSystem() { return m_renderSystem; }
    UpdateSystem& getUpdateSystem() { return m_updateSystem; }

private:
    std::vector<Entity> m_entityVector;

    InputSystem m_inputSystem;
    RenderSystem m_renderSystem;
    UpdateSystem m_updateSystem;
};