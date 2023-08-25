#pragma once

union SDL_Event;
struct SDL_Renderer;

class AbstractState
{
public:
    AbstractState(SDL_Renderer& rendererRef) : m_rendererRef(rendererRef) {}
    virtual ~AbstractState() = default;
    virtual void handleInput(const SDL_Event& event) = 0;
    virtual void updateState(unsigned int deltaTime) = 0;
    virtual void renderState() = 0;

protected:
    SDL_Renderer& m_rendererRef;
};