#pragma once

struct Vec2D;

class RigidBody
{
public:
    explicit RigidBody(float mass);
    ~RigidBody() = default;

    void applyForceX(float forceX);
    void applyForceY(float forceY);
    void multiplyForceX(float coeffX);
    void multiplyForceY(float coeffY);
    void updateWithDeltaTime(unsigned int deltaTime);
    int getPosX() const;
    int getPosY() const;
    
private:
    float m_mass;

    Vec2D m_forceVector;    
    Vec2D m_accelerationVec;
    Vec2D m_velocityVec;
    Vec2D m_positionVec;
};