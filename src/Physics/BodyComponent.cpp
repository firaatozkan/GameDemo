#include "ECS/Entity.hpp"
#include "Physics/BodyComponent.hpp"
#include "Physics/TransformComponent.hpp"

using namespace Physics;

BodyComponent::BodyComponent(ECS::Entity& entityRef, float mass) :
    ECS::Component(entityRef),
    m_mass(mass),
    m_forceVector {0, 0},
    m_accelerationVector {0, 0},
    m_velocityVector {0, 0}
{
}

void BodyComponent::update(const std::chrono::steady_clock::duration& deltaTime)
{
    float frictionForce = m_velocityVector.X * 1.2f;

    m_accelerationVector.X = (m_forceVector.X - frictionForce) / m_mass;
    m_accelerationVector.Y = (m_forceVector.Y) / m_mass;

    m_velocityVector.X += m_accelerationVector.X * std::chrono::duration_cast<std::chrono::milliseconds>(deltaTime).count();
    m_velocityVector.Y += m_accelerationVector.Y * std::chrono::duration_cast<std::chrono::milliseconds>(deltaTime).count();

    Vector2D& positionVector = m_entityRef.getComponent<TransformComponent>().getPositionVector();
    positionVector.X += m_velocityVector.X * std::chrono::duration_cast<std::chrono::milliseconds>(deltaTime).count();
    positionVector.Y += m_velocityVector.Y * std::chrono::duration_cast<std::chrono::milliseconds>(deltaTime).count();

    m_forceVector.X = 0;
    m_forceVector.Y = 0;
}

void BodyComponent::applyForceX(float force)
{
    m_forceVector.X = force;
}

void BodyComponent::applyForceY(float force)
{
    m_forceVector.Y = force;
}