#pragma once

#include <vector>
#include <SDL2/SDL.h>
#include "Core/AbstractGameState.hpp"
#include "Core/Levels/BaseGameLevel.hpp"

#include "Core/IObject.hpp"
#include "Core/IInputable.hpp"
#include "Graphics/IRenderable.hpp"
#include "Physics/IBody.hpp"
#include "Physics/ICollidable.hpp"

template <typename T>
class BaseGameLevel : public AbstractGameState
{
public:
    BaseGameLevel(SDL_Renderer& rendererRef) : AbstractGameState(rendererRef) 
    {
        static_cast<T*>(this)->initializeGameObjects();
    }

    virtual ~BaseGameLevel()
    {
        for (auto object : m_objectVector)
            delete object;
    }

    void handleInput(const SDL_Event& event, bool& gameRunning) override
    {
        if (event.type == SDL_QUIT)
        {
            /* for now, later will pop-up the menu */
            gameRunning = false;
            return;
        }
        for (auto inputable : m_inputableVector)
            inputable->handleInput(event);
    }

    void updateState(Uint32 deltaTime) override
    {
        for (auto body : m_bodyVector)
            body->applyPhysics(deltaTime);

        for (size_t i = 0; i < m_collidableVector.size(); ++i)
        {
            for (size_t j = i + 1; j < m_collidableVector.size(); ++j)
            {
                if (m_collidableVector[i]->doesCollideWith(m_collidableVector[j]))
                    m_collidableVector[i]->applyCollision(m_collidableVector[j]);
            }
        }
    }

    void renderObjects() override
    {
        SDL_SetRenderDrawColor(&m_rendererRef, T::rgba_r, T::rgba_g, T::rgba_b, T::rgba_a);
        SDL_RenderClear(&m_rendererRef);

        for (auto renderable : m_renderableVector)
            renderable->render();

        SDL_RenderPresent(&m_rendererRef);
    }

protected:
    std::vector<IObject*> m_objectVector;
    std::vector<IInputable*> m_inputableVector;
    std::vector<IRenderable*> m_renderableVector;
    std::vector<IBody*> m_bodyVector;
    std::vector<ICollidable*> m_collidableVector;
};