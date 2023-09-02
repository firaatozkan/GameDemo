/**
 * @file AnimationComponent.cpp
 * @brief Implements the AnimationComponent class for managing animations.
 */

#include "ECS/Entity.hpp"
#include "Physics/TransformComponent.hpp"
#include "Graphics/AnimationComponent.hpp"

using namespace Graphics;

/**
 * @brief Constructs an AnimationComponent with animations and a current animation.
 *
 * The constructor initializes an AnimationComponent for a specified entity with a list
 * of animations and the name of the current animation.
 *
 * @param entityRef Reference to the entity this component belongs to.
 * @param animationList A list of animations to associate with this component.
 * @param currentAnimation The name of the current animation.
 */
AnimationComponent::AnimationComponent(ECS::Entity& entityRef,
                                       const Animation::List& animationList,
                                       const std::string& currentAnimation) :
    ECS::Component(entityRef), /**< Initialize the base class Component with the entity reference. */
    m_currentAnimation(currentAnimation) /**< Initialize the current animation. */
{
    // Populate the animation map with animations from the provided list.
    for (const auto& animation : animationList)
        m_animationMap.emplace(animation.first, animation.second);
}

/**
 * @brief Renders the current animation at the entity's position.
 *
 * The render method renders the current animation at the entity's position,
 * taking into account whether it should be flipped horizontally.
 */
void AnimationComponent::render()
{
    // Render the current animation at the entity's position with optional horizontal flip.
    m_animationMap[m_currentAnimation]->renderAt(
        m_entityRef.getComponent<Physics::TransformComponent>().getPositionX(),
        m_entityRef.getComponent<Physics::TransformComponent>().getPositionY(),
        m_isFlipped
    );
}

/**
 * @brief Updates the animation component based on elapsed time.
 *
 * The update method advances the animation frames based on the elapsed time
 * since the last update, ensuring that the animation progresses smoothly.
 *
 * @param deltaTime The time duration since the last update.
 */
void AnimationComponent::update(const std::chrono::steady_clock::duration& deltaTime)
{
    // Accumulate the time since the last frame change.
    m_totalTime += deltaTime;

    // Set a frame change interval (e.g., 60 milliseconds).
    using namespace std::chrono_literals;

    // If enough time has passed, advance to the next frame.
    if (m_totalTime > 60ms)
    {
        m_animationMap[m_currentAnimation]->nextFrame();
        m_totalTime = 0ns; // Reset the time accumulator.
    }
}

/**
 * @brief Sets the current animation by name.
 *
 * The setAnimation method allows changing the current animation to another one
 * in the list of available animations.
 *
 * @param name The name of the animation to set as the current animation.
 */
void AnimationComponent::setAnimation(const std::string& name)
{
    m_currentAnimation = name;
}

/**
 * @brief Flips the current animation horizontally if specified.
 *
 * The flip method allows flipping the current animation horizontally if needed.
 *
 * @param input Boolean indicating whether to flip the animation horizontally.
 */
void AnimationComponent::flip(bool input)
{
    m_isFlipped = input;
}
