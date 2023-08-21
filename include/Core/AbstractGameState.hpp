#pragma once

struct SDL_Renderer;
union SDL_Event;

class AbstractGameState
{
public:
    AbstractGameState(SDL_Renderer& rendererRef) : m_rendererRef(rendererRef) {}
    virtual ~AbstractGameState() = default;
    virtual void handleInput(const SDL_Event& event, bool& gameRunning) = 0;
    virtual void updateState(Uint32 deltaTime) = 0;
    virtual void renderObjects() = 0;

protected:
    SDL_Renderer& m_rendererRef;
};