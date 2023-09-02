/**
 * @file TransformComponent.cpp
 * @brief Implements the TransformComponent class for managing entity positions.
 */

#include "Physics/TransformComponent.hpp"

using namespace Physics;

/**
 * @brief Constructs a TransformComponent with initial position coordinates.
 *
 * The constructor initializes a TransformComponent associated with a specific entity
 * and sets its initial position based on the provided (x, y) coordinates.
 *
 * @param entityRef Reference to the entity this component belongs to.
 * @param x The initial X-coordinate of the entity's position.
 * @param y The initial Y-coordinate of the entity's position.
 */
TransformComponent::TransformComponent(ECS::Entity& entityRef, float x, float y) :
    ECS::Component(entityRef), /**< Initialize the base class Component with the entity reference. */
    m_positionVector {x, y} /**< Initialize the position vector with the provided (x, y) coordinates. */
{
}

/**
 * @brief Gets a reference to the position vector.
 *
 * The getPositionVector method returns a reference to the position vector, allowing direct modification of the entity's position.
 *
 * @return A reference to the entity's position vector.
 */
Vector2D& TransformComponent::getPositionVector()
{
    return m_positionVector;
}

/**
 * @brief Gets a constant reference to the position vector.
 *
 * The getPositionVector method returns a constant reference to the position vector, preventing direct modification of the entity's position.
 *
 * @return A constant reference to the entity's position vector.
 */
const Vector2D& TransformComponent::getPositionVector() const
{
    return m_positionVector;
}

/**
 * @brief Gets the X-coordinate of the entity's position.
 *
 * The getPositionX method returns the X-coordinate of the entity's position.
 *
 * @return The X-coordinate of the entity's position.
 */
float TransformComponent::getPositionX() const
{
    return m_positionVector.X;
}

/**
 * @brief Gets the Y-coordinate of the entity's position.
 *
 * The getPositionY method returns the Y-coordinate of the entity's position.
 *
 * @return The Y-coordinate of the entity's position.
 */
float TransformComponent::getPositionY() const
{
    return m_positionVector.Y;
}
