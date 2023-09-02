/**
 * @file BodyComponent.cpp
 * @brief Implements the BodyComponent class for simulating physical behavior.
 */

#include "ECS/Entity.hpp"
#include "Physics/BodyComponent.hpp"
#include "Physics/TransformComponent.hpp"

using namespace Physics;

/**
 * @brief Constructs a BodyComponent with a specified mass.
 *
 * The constructor initializes a BodyComponent associated with a specific entity and sets its mass,
 * along with initializing other physical properties.
 *
 * @param entityRef Reference to the entity this component belongs to.
 * @param mass The mass of the entity associated with this body component.
 */
BodyComponent::BodyComponent(ECS::Entity& entityRef, float mass) :
    ECS::Component(entityRef), /**< Initialize the base class Component with the entity reference. */
    m_mass(mass), /**< Initialize the mass of the body. */
    m_forceVector {0, 0}, /**< Initialize the force vector to zero. */
    m_accelerationVector {0, 0}, /**< Initialize the acceleration vector to zero. */
    m_velocityVector {0, 0} /**< Initialize the velocity vector to zero. */
{
}

/**
 * @brief Updates the body component based on physics calculations.
 *
 * The update method simulates the entity's physics behavior, including handling forces,
 * friction, acceleration, velocity, and position updates.
 *
 * @param deltaTime The time duration since the last physics update.
 */
void BodyComponent::update(const std::chrono::steady_clock::duration& deltaTime)
{
    // Calculate friction force based on velocity.
    float frictionForce = m_velocityVector.X * 1.2f;

    // Calculate acceleration in X and Y directions.
    m_accelerationVector.X = (m_forceVector.X - frictionForce) / m_mass;
    m_accelerationVector.Y = (m_forceVector.Y) / m_mass;

    // Update velocity based on acceleration and time.
    m_velocityVector.X += m_accelerationVector.X * std::chrono::duration_cast<std::chrono::milliseconds>(deltaTime).count();
    m_velocityVector.Y += m_accelerationVector.Y * std::chrono::duration_cast<std::chrono::milliseconds>(deltaTime).count();

    // Update the entity's position based on velocity and time.
    Vector2D& positionVector = m_entityRef.getComponent<TransformComponent>().getPositionVector();
    positionVector.X += m_velocityVector.X * std::chrono::duration_cast<std::chrono::milliseconds>(deltaTime).count();
    positionVector.Y += m_velocityVector.Y * std::chrono::duration_cast<std::chrono::milliseconds>(deltaTime).count();

    // Reset the force vector to zero for the next update.
    m_forceVector.X = 0;
    m_forceVector.Y = 0;
}

/**
 * @brief Applies a force in the X direction.
 *
 * The applyForceX method applies a force to the body component in the X direction.
 *
 * @param force The force to apply in the X direction.
 */
void BodyComponent::applyForceX(float force)
{
    m_forceVector.X = force;
}

/**
 * @brief Applies a force in the Y direction.
 *
 * The applyForceY method applies a force to the body component in the Y direction.
 *
 * @param force The force to apply in the Y direction.
 */
void BodyComponent::applyForceY(float force)
{
    m_forceVector.Y = force;
}
