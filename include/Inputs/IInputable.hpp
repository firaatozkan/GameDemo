/**
 * @file IInputable.hpp
 * @brief Defines the IInputable interface for input handling.
 */

#pragma once

union SDL_Event;

namespace Inputs
{
    /**
     * @class IInputable
     * @brief An interface for handling input events.
     *
     * The IInputable interface defines a contract for classes that can handle
     * input events, such as keyboard and mouse events. Classes implementing this
     * interface should provide the ability to respond to input events.
     */
    class IInputable
    {
    public:
        /**
         * @brief Virtual destructor for proper cleanup in derived classes.
         */
        virtual ~IInputable() = default;

        /**
         * @brief Handles the specified input event.
         *
         * @param event The SDL event to handle.
         */
        virtual void handleInput(const SDL_Event& event) = 0;
    };
}
