/**
 * @file KeyboardController.hpp
 * @brief Defines the KeyboardController class for handling keyboard input.
 */

#pragma once

#include "ECS/Component.hpp"
#include "Inputs/IInputable.hpp"

namespace Inputs
{
    /**
     * @class KeyboardController
     * @brief Represents a component for handling keyboard input.
     *
     * The KeyboardController class extends the ECS::Component class and implements
     * the IInputable interface to handle keyboard input events for an entity.
     */
    class KeyboardController : 
        public ECS::Component,
        public IInputable
    {
    public:
        /**
         * @brief Constructs a KeyboardController object.
         *
         * @param entityRef Reference to the entity this component belongs to.
         */
        KeyboardController(ECS::Entity& entityRef);

        /**
         * @brief Destructor for cleaning up resources.
         */
        ~KeyboardController() = default;

        /**
         * @brief Handles keyboard input events.
         *
         * @param event The SDL event representing the keyboard input event.
         */
        void handleInput(const SDL_Event& event) override;
    };
}
