#include <SDL2/SDL.h>
#include "ECS/World.hpp"

void World::handleInput(const SDL_Event& event)
{
    m_inputSystem.runSystem(event);
}

void World::updateWorld(unsigned int deltaTime)
{
    m_updateSystem.runSystem(deltaTime);
}

void World::renderWorld()
{
    m_renderSystem.runSystem();
}

Entity& World::createEntity()
{
    return m_entityVector.emplace_back(*this);
}