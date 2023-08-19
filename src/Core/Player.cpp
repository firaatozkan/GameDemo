#include <vector>
#include <chrono>
#include <SDL2/SDL.h>
#include "Physics/Vec2D.hpp"
#include "Graphics/IRenderable.hpp"
#include "Physics/IUpdatable.hpp"
#include "Physics/RigidBody.hpp"
#include "Graphics/Animation.hpp"
#include "Core/Player.hpp"

Player::Player(SDL_Renderer& rendererRef)
    : RigidBody(50.0f)
{
    m_animationArray[IDLE] = new Animation(rendererRef, PROJECT_SOURCE_DIR"/assets/Archer/Idle.png", 6);
    m_animationArray[WALK] = new Animation(rendererRef, PROJECT_SOURCE_DIR"/assets/Archer/Walk.png", 8);
    m_animationArray[JUMP] = new Animation(rendererRef, PROJECT_SOURCE_DIR"/assets/Archer/Jump.png", 9);
    m_animationArray[RUN] = new Animation(rendererRef, PROJECT_SOURCE_DIR"/assets/Archer/Run.png", 8);
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
                if (m_currentState != JUMP)
                {
                    m_currentState = WALK;
                    m_isFacingRight = true;
                    this->applyForceX(600.0f);
                }
                break;

            case SDLK_LEFT:
                [[fallthrough]];
            case SDLK_a:
                if (m_currentState != JUMP)
                {
                    m_currentState = WALK;
                    m_isFacingRight = false;
                    this->applyForceX(-600.0f);
                }
                break;

            case SDLK_LSHIFT:
                if (m_currentState == WALK)
                {
                    m_currentState = RUN;
                    this->multiplyForceX(2.0f);
                }
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
                this->applyForceX(0.0f);
                break;

            case SDLK_LSHIFT:
                if (m_currentState == RUN)
                    m_currentState = WALK;
                break;
                
            default:
                break;
        }
    }
}

void Player::render()
{
    m_animationArray[m_currentState]->renderAt(this->getPosX(), this->getPosY(), m_isFacingRight);
}

void Player::update(unsigned int deltaTime)
{
    m_lastDuration += deltaTime;

    if (m_lastDuration >= 120)
    {
        if (m_currentState == JUMP)
        {
            if (m_animationArray[m_currentState]->isFinished())
            {
                m_animationArray[m_currentState]->resetFrame();
                m_currentState = IDLE;
                goto ResetDuration;
            }
        }
        m_animationArray[m_currentState]->nextFrame();

ResetDuration:
        m_lastDuration = 0;
    }

    this->updateWithDeltaTime(deltaTime);
}