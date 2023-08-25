#pragma once

#include "ECS/Components/BaseComponent.hpp"

struct SDL_Renderer;

class BaseRenderableComponent : public BaseComponent
{
public:
    BaseRenderableComponent(Entity& entityRef, SDL_Renderer& rendererRef) : 
        BaseComponent(entityRef),
        m_rendererRef(rendererRef)
    {
    }

    virtual ~BaseRenderableComponent() = default;
    virtual void render() = 0;

protected:
    SDL_Renderer& m_rendererRef;
};