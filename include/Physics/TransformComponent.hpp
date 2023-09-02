#pragma once

#include "ECS/Component.hpp"
#include "Physics/Vector2D.hpp"

namespace Physics
{
    class TransformComponent : public ECS::Component
    {
    public:
        TransformComponent(ECS::Entity& entityRef, float x, float y);
        ~TransformComponent() = default;
        
        Vector2D& getPositionVector();
        const Vector2D& getPositionVector() const;

        float getPositionX() const;
        float getPositionY() const;

    private:
        Vector2D m_positionVector;
    };
}