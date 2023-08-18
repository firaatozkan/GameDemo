#include <SDL2/SDL.h>
#include "AbstractGameState.hpp"
#include "Level_1.hpp"
#include "IRenderable.hpp"
#include "IUpdatable.hpp"
#include "Vec2D.hpp"
#include "Player.hpp"

Level_1::Level_1(SDL_Renderer& rendererRef)
    : AbstractGameState(rendererRef)
{
    m_player = new Player(m_rendererRef);
    m_renderableVector.push_back(m_player);
    m_updatableVector.push_back(m_player);
}

Level_1::~Level_1()
{
    delete m_player;
}

void Level_1::handleInput(const SDL_Event& input, bool& gameRunningFlag)
{
    if (input.type == SDL_QUIT)
        gameRunningFlag = false;
    else
        m_player->handleInput(input);
}

void Level_1::renderObjects(void)
{
    SDL_RenderClear(&m_rendererRef);

    for (auto renderable : m_renderableVector)
        renderable->render();

    SDL_RenderPresent(&m_rendererRef);
}

void Level_1::updateState(unsigned int deltaTime)
{
    for (auto updatable : m_updatableVector)
        updatable->update(deltaTime);
}