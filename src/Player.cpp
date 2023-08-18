#include <vector>
#include <chrono>
#include <SDL2/SDL.h>
#include "IRenderable.hpp"
#include "IUpdatable.hpp"
#include "Animation.hpp"
#include "Vec2D.hpp"
#include "Player.hpp"

Player::Player(SDL_Renderer& rendererRef)
{
    m_animationArray[IDLE] = new Animation(rendererRef, R"(C:\Users\foska\Cpp\GameDemo\assets\Archer\Idle.png)", 6);
    m_animationArray[WALK] = new Animation(rendererRef, R"(C:\Users\foska\Cpp\GameDemo\assets\Archer\Walk.png)", 8);
    m_animationArray[JUMP] = new Animation(rendererRef, R"(C:\Users\foska\Cpp\GameDemo\assets\Archer\Jump.png)", 9);
}

Player::~Player()
{
    for (size_t i = 0; i < NUM_OF_PLAYER_STATES; ++i)
        delete m_animationArray[i];
}

void Player::handleInput(const SDL_Event& event)
{
    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
            case SDLK_SPACE:
                m_currentState = JUMP;
                break;

            case SDLK_RIGHT:
                [[fallthrough]];
            case SDLK_d:
                m_currentState = WALK;
                m_isFacingRight = true;
                m_forceVector.x = 1275.0f;
                m_frictionVector.x = 10.0f * 50.0f * 2.0f;
                break;

            case SDLK_LEFT:
                [[fallthrough]];
            case SDLK_a:
                m_currentState = WALK;
                m_isFacingRight = false;
                m_forceVector.x = -1275.0f;
                m_frictionVector.x = -10.0f * 50.0f * 2.0f;
                break;
            
            default:
                break;
        }
    }
    else if (event.type == SDL_KEYUP)
    {
        switch (event.key.keysym.sym)
        {
            case SDLK_RIGHT:
                [[fallthrough]];
            case SDLK_d:
                [[fallthrough]];
            case SDLK_LEFT:
                [[fallthrough]];
            case SDLK_a:
                m_currentState = IDLE;
                m_forceVector.x = 0;
                break;

            default:
                break;
        }
    }
}

void Player::render()
{
    m_animationArray[m_currentState]->renderAt(static_cast<int>(m_positionVec.x), static_cast<int>(m_positionVec.y), m_isFacingRight);
}

void Player::update(unsigned int deltaTime)
{
    m_lastDuration += deltaTime;

    if (m_lastDuration >= 1e2)
    {
        if (m_currentState == JUMP)
        {
            if (m_animationArray[m_currentState]->isFinished())
            {
                m_animationArray[m_currentState]->resetFrame();
                m_currentState = IDLE;
                goto Physics;
            }
        }
        m_animationArray[m_currentState]->nextFrame();
        m_lastDuration = 0;
    }

Physics:
    m_accelerationVec.x = (m_forceVector.x - m_frictionVector.x) / 50.0f;
    m_velocityVec.x += m_accelerationVec.x * (static_cast<float>(deltaTime) / 1e2f);
    m_positionVec.x = m_velocityVec.x * (static_cast<float>(deltaTime) / 1e2f) + 0.5f * m_accelerationVec.x * ((static_cast<float>(deltaTime) / 1e2f) * (static_cast<float>(deltaTime) / 1e2f));

    m_forceVector.x = 0;
    m_frictionVector.x = 0;
}