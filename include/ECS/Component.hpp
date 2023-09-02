/**
 * @file Component.hpp
 * @brief Defines the Component class for game entities.
 */

#pragma once

namespace ECS
{
    class Entity;

    /**
     * @class Component
     * @brief Base class for game components associated with entities.
     *
     * The Component class serves as the base class for various components
     * that can be attached to game entities. Each component is associated with
     * a specific entity and provides functionality or data to that entity.
     */
    class Component
    {
    public:
        /**
         * @brief Constructor for creating a component associated with an entity.
         * @param entityRef Reference to the entity this component belongs to.
         */
        Component(Entity& entityRef) : m_entityRef(entityRef) {}

        /**
         * @brief Virtual destructor for proper cleanup in derived classes.
         */
        virtual ~Component() = default;

    protected:
        Entity& m_entityRef; /**< Reference to the entity this component belongs to. */
    };
}
