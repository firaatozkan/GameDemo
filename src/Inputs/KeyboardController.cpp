#include <SDL2/SDL.h>
#include "ECS/Entity.hpp"
#include "Physics/BodyComponent.hpp"
#include "Inputs/KeyboardController.hpp"
#include "Graphics/AnimationComponent.hpp"

using namespace Inputs;

KeyboardController::KeyboardController(ECS::Entity& entityRef) :
    ECS::Component(entityRef)
{
}

void KeyboardController::handleInput(const SDL_Event& event)
{
    if (event.type == SDL_KEYDOWN)
    {
        if (event.key.keysym.sym == SDLK_RIGHT)        
        {
            m_entityRef.getComponent<Physics::BodyComponent>().applyForceX(1.0f);
            m_entityRef.getComponent<Graphics::AnimationComponent>().setAnimation("Walk");
            m_entityRef.getComponent<Graphics::AnimationComponent>().flip(false);
        }
        else if (event.key.keysym.sym == SDLK_LEFT)        
        {
            m_entityRef.getComponent<Physics::BodyComponent>().applyForceX(-1.0f);
            m_entityRef.getComponent<Graphics::AnimationComponent>().setAnimation("Walk");
            m_entityRef.getComponent<Graphics::AnimationComponent>().flip(true);
        }
    }
    else if (event.type == SDL_KEYUP)
    {
        if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_LEFT)
        {
            m_entityRef.getComponent<Graphics::AnimationComponent>().setAnimation("Idle");
        }
    }
}