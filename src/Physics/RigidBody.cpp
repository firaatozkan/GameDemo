#include "Physics/Vec2D.hpp"
#include "Physics/RigidBody.hpp"

RigidBody::RigidBody(float mass)
    : m_mass(mass)
{
}

void RigidBody::applyForceX(float forceX)
{
    m_forceVector.x = forceX;
}

void RigidBody::applyForceY(float forceY)
{
    m_forceVector.y = forceY;
}

void RigidBody::multiplyForceX(float coeffX)
{
    m_forceVector.x *= coeffX;
}

void RigidBody::multiplyForceY(float coeffY)
{
    m_forceVector.y *= coeffY;
}

void RigidBody::updateWithDeltaTime(unsigned int deltaTime)
{
    float frictionForce = 0.9f * m_velocityVec.x * m_mass;
    m_accelerationVec.x = (m_forceVector.x - frictionForce) / m_mass;
    m_velocityVec.x += m_accelerationVec.x * (static_cast<float>(deltaTime) / 1e2f);
    m_positionVec.x += m_velocityVec.x * (static_cast<float>(deltaTime) / 1e2f);
}

int RigidBody::getPosX() const
{
    return static_cast<int>(m_positionVec.x);
}

int RigidBody::getPosY() const
{
    return static_cast<int>(m_positionVec.y);
}