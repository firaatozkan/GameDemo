#pragma once

class AbstractGameState
{
public:
    AbstractGameState(SDL_Renderer& rendererRef) : m_rendererRef(rendererRef) {}
    virtual ~AbstractGameState() = default;
    virtual void handleInput(const SDL_Event& input, bool& gameRunningFlag) = 0;
    virtual void renderObjects(void) = 0;
    virtual void updateState(unsigned int deltaTime) = 0;

protected:
    SDL_Renderer& m_rendererRef;
};