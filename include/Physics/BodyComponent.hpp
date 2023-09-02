#pragma once

#include "ECS/Component.hpp"
#include "Physics/Vector2D.hpp"
#include "Physics/IUpdatable.hpp"

namespace Physics
{
    class BodyComponent : 
        public ECS::Component,
        public IUpdatable
    {
    public:
        BodyComponent(ECS::Entity& entityRef, float mass);
        ~BodyComponent() = default;
        void update(const std::chrono::steady_clock::duration& deltaTime) override;

        void applyForceX(float force);
        void applyForceY(float force);

    private:
        float m_mass;
        Vector2D m_forceVector;
        Vector2D m_accelerationVector;
        Vector2D m_velocityVector;
    };
}