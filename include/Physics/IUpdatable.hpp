/**
 * @file IUpdatable.hpp
 * @brief Defines the IUpdatable interface for objects with update functionality.
 */

#pragma once

#include <chrono>

namespace Physics
{
    /**
     * @class IUpdatable
     * @brief An interface for objects with update functionality.
     *
     * The IUpdatable interface defines a contract for classes that can be updated
     * over time. Classes implementing this interface should provide the ability
     * to perform updates based on a given time duration.
     */
    class IUpdatable
    {
    public:
        /**
         * @brief Virtual destructor for proper cleanup in derived classes.
         */
        virtual ~IUpdatable() = default;

        /**
         * @brief Updates the object based on the elapsed time.
         *
         * @param deltaTime The time duration since the last update.
         */
        virtual void update(const std::chrono::steady_clock::duration& deltaTime) = 0;
    };
}
