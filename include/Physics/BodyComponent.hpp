/**
 * @file BodyComponent.hpp
 * @brief Defines the BodyComponent class for physics simulation.
 */

#pragma once

#include "ECS/Component.hpp"
#include "Physics/Vector2D.hpp"
#include "Physics/IUpdatable.hpp"

namespace Physics
{
    /**
     * @class BodyComponent
     * @brief Represents a component for physics simulation.
     *
     * The BodyComponent class extends the ECS::Component class and implements
     * the IUpdatable interface to simulate physics behavior for an entity.
     */
    class BodyComponent : 
        public ECS::Component,
        public IUpdatable
    {
    public:
        /**
         * @brief Constructs a BodyComponent object.
         *
         * @param entityRef Reference to the entity this component belongs to.
         * @param mass The mass of the entity for physics calculations.
         */
        BodyComponent(ECS::Entity& entityRef, float mass);

        /**
         * @brief Destructor for cleaning up resources.
         */
        ~BodyComponent() = default;

        /**
         * @brief Updates the physics simulation over time.
         *
         * @param deltaTime The time elapsed since the last update.
         */
        void update(const std::chrono::steady_clock::duration& deltaTime) override;

        /**
         * @brief Applies a force in the X-axis direction to the entity.
         *
         * @param force The force to apply in the X-axis direction.
         */
        void applyForceX(float force);

        /**
         * @brief Applies a force in the Y-axis direction to the entity.
         *
         * @param force The force to apply in the Y-axis direction.
         */
        void applyForceY(float force);

    private:
        float m_mass; /** The mass of the entity for physics calculations. */
        Vector2D m_forceVector; /** The accumulated force vector applied to the entity. */
        Vector2D m_accelerationVector; /** The calculated acceleration vector of the entity. */
        Vector2D m_velocityVector; /** The velocity vector of the entity. */
    };
}
