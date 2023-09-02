/**
 * @file Entity.hpp
 * @brief Defines the Entity class for game entities and components.
 */

#pragma once

#include <memory>
#include <typeindex>
#include <unordered_map>

namespace ECS
{
    class Component;

    /**
     * @class Entity
     * @brief Represents a game entity with components.
     *
     * The Entity class is responsible for managing components associated with a game entity.
     * It allows adding, retrieving, and managing components attached to the entity.
     */
    class Entity
    {
    public:
        /**
         * @brief Default constructor for creating an entity.
         */
        Entity() = default;

        /**
         * @brief Virtual destructor for proper cleanup of derived classes.
         */
        virtual ~Entity() = default;

        /**
         * @brief Adds a component of type T to the entity.
         *
         * This method creates and attaches a new component of type T to the entity.
         *
         * @tparam T The type of the component to add.
         * @tparam Args Parameter pack for forwarding constructor arguments.
         * @param args Constructor arguments for creating the component.
         * @return Reference to the added component.
         */
        template <typename T, typename... Args, typename = std::enable_if_t<std::is_base_of_v<Component, T>>>
        T& addComponent(Args&&... args)
        {
            m_componentMap.emplace(typeid(T), std::make_unique<T>(*this, std::forward<Args>(args)...));
            return *(reinterpret_cast<T*>(m_componentMap[typeid(T)].get()));
        }

        /**
         * @brief Gets a component of type T from the entity.
         *
         * This method retrieves a component of type T that is attached to the entity.
         *
         * @tparam T The type of the component to retrieve.
         * @return Reference to the retrieved component.
         */
        template <typename T, typename = std::enable_if_t<std::is_base_of_v<Component, T>>>
        T& getComponent()
        {
            return *(reinterpret_cast<T*>(m_componentMap[typeid(T)].get()));
        }

        /**
         * @brief Gets the map of components associated with the entity.
         * @return Reference to the map of components.
         */
        std::unordered_map<std::type_index, std::unique_ptr<Component>>& getComponentMap() { return m_componentMap; }

        /**
         * @brief Gets the map of components associated with the entity (const version).
         * @return Const reference to the map of components.
         */
        const std::unordered_map<std::type_index, std::unique_ptr<Component>>& getComponentMap() const { return m_componentMap; }

    private:
        std::unordered_map<std::type_index, std::unique_ptr<Component>> m_componentMap; /**< Map of components associated with the entity. */
    };
}
