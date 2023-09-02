/**
 * @file KeyboardController.cpp
 * @brief Implements the KeyboardController class for handling keyboard input.
 */

#include <SDL2/SDL.h>
#include "ECS/Entity.hpp"
#include "Physics/BodyComponent.hpp"
#include "Graphics/AnimationComponent.hpp"
#include "Inputs/KeyboardController.hpp"

using namespace Inputs;

/**
 * @brief Constructs a KeyboardController for handling keyboard input.
 *
 * The constructor initializes a KeyboardController associated with a specific entity.
 *
 * @param entityRef Reference to the entity this component belongs to.
 */
KeyboardController::KeyboardController(ECS::Entity& entityRef) :
    ECS::Component(entityRef) /**< Initialize the base class Component with the entity reference. */
{
}

/**
 * @brief Handles keyboard input events to control the entity's behavior.
 *
 * The handleInput method handles SDL keyboard events to control the entity's behavior,
 * including moving left or right and updating the associated animation accordingly.
 *
 * @param event The SDL event to handle.
 */
void KeyboardController::handleInput(const SDL_Event& event)
{
    if (event.type == SDL_KEYDOWN)
    {
        if (event.key.keysym.sym == SDLK_RIGHT)
        {
            // Apply a positive force in the X-axis and set the animation to "Walk" (unflipped).
            m_entityRef.getComponent<Physics::BodyComponent>().applyForceX(1.0f);
            m_entityRef.getComponent<Graphics::AnimationComponent>().setAnimation("Walk");
            m_entityRef.getComponent<Graphics::AnimationComponent>().flip(false);
        }
        else if (event.key.keysym.sym == SDLK_LEFT)
        {
            // Apply a negative force in the X-axis and set the animation to "Walk" (flipped).
            m_entityRef.getComponent<Physics::BodyComponent>().applyForceX(-1.0f);
            m_entityRef.getComponent<Graphics::AnimationComponent>().setAnimation("Walk");
            m_entityRef.getComponent<Graphics::AnimationComponent>().flip(true);
        }
    }
    else if (event.type == SDL_KEYUP)
    {
        if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_LEFT)
        {
            // Set the animation to "Idle" when no movement keys are pressed.
            m_entityRef.getComponent<Graphics::AnimationComponent>().setAnimation("Idle");
        }
    }
}
