/**
 * @file TransformComponent.hpp
 * @brief Defines the TransformComponent class for managing entity positions.
 */

#pragma once

#include "ECS/Component.hpp"
#include "Physics/Vector2D.hpp"

namespace Physics
{
    /**
     * @class TransformComponent
     * @brief Represents a component for managing entity positions.
     *
     * The TransformComponent class extends the ECS::Component class to manage
     * the position of an entity in a 2D space.
     */
    class TransformComponent : public ECS::Component
    {
    public:
        /**
         * @brief Constructs a TransformComponent object with an initial position.
         *
         * @param entityRef Reference to the entity this component belongs to.
         * @param x The initial X-coordinate of the entity's position.
         * @param y The initial Y-coordinate of the entity's position.
         */
        TransformComponent(ECS::Entity& entityRef, float x, float y);

        /**
         * @brief Destructor for cleaning up resources.
         */
        ~TransformComponent() = default;

        /**
         * @brief Gets a reference to the entity's position vector.
         *
         * @return Reference to the entity's position vector.
         */
        Vector2D& getPositionVector();

        /**
         * @brief Gets a const reference to the entity's position vector.
         *
         * @return Const reference to the entity's position vector.
         */
        const Vector2D& getPositionVector() const;

        /**
         * @brief Gets the X-coordinate of the entity's position.
         *
         * @return The X-coordinate of the entity's position.
         */
        float getPositionX() const;

        /**
         * @brief Gets the Y-coordinate of the entity's position.
         *
         * @return The Y-coordinate of the entity's position.
         */
        float getPositionY() const;

    private:
        Vector2D m_positionVector; /** The position vector of the entity in 2D space. */
    };
}
