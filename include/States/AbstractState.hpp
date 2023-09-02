/**
 * @file AbstractState.hpp
 * @brief Defines the AbstractState class for game states.
 */

#pragma once

union SDL_Event;

namespace States
{
    /**
     * @class AbstractState
     * @brief An abstract base class for representing game states.
     *
     * The AbstractState class defines a contract for representing game states.
     * Classes derived from this abstract base class should implement methods
     * to handle input, update game logic, and render the state.
     */
    class AbstractState
    {
    public:
        /**
         * @brief Virtual destructor for proper cleanup in derived classes.
         */
        virtual ~AbstractState() = default;

        /**
         * @brief Handles input events for the game state.
         *
         * @param event The SDL event to handle.
         */
        virtual void handleInput(const SDL_Event& event) = 0;

        /**
         * @brief Updates the game state based on the elapsed time.
         *
         * @param deltaTime The time duration since the last update.
         */
        virtual void updateState(const std::chrono::steady_clock::duration& deltaTime) = 0;

        /**
         * @brief Renders the current game state.
         */
        virtual void renderState() = 0;
    };
}
