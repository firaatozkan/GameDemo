#pragma once

#include <vector>
#include <SDL2/SDL.h>
#include "States/AbstractState.hpp"
#include "ECS/World.hpp"

template <typename T>
class AbstractLevel : public AbstractState
{
public:
    AbstractLevel(SDL_Renderer& rendererRef) :
        AbstractState(rendererRef)
    {
        static_cast<T*>(this)->initializeWorld();
    }

    virtual ~AbstractLevel() = default;

    void handleInput(const SDL_Event& event) override
    {
        if (event.type == SDL_QUIT)
            exit(EXIT_SUCCESS);

        m_world.handleInput(event);
    }

    void updateState(unsigned int deltaTime) override
    {
        m_world.updateWorld(deltaTime);
    }

    void renderState() override
    {
        m_world.renderWorld();
    }

protected:
    World m_world;
};