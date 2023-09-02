#include "Physics/TransformComponent.hpp"

using namespace Physics;

TransformComponent::TransformComponent(ECS::Entity& entityRef, float x, float y) :
    ECS::Component(entityRef),
    m_positionVector {x, y}
{
}

Vector2D& TransformComponent::getPositionVector()
{
    return m_positionVector;
}

const Vector2D& TransformComponent::getPositionVector() const
{
    return m_positionVector;
}

float TransformComponent::getPositionX() const
{
    return m_positionVector.X;
}

float TransformComponent::getPositionY() const
{
    return m_positionVector.Y;
}