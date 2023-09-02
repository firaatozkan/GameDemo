/**
 * @file Player.hpp
 * @brief Defines the Player class for representing a game player.
 */

#pragma once

#include "ECS/Entity.hpp"

namespace Assets
{
    /**
     * @class Player
     * @brief Represents a game player entity.
     *
     * The Player class extends the ECS::Entity class to define a game player entity.
     * It provides the basic structure for creating and managing player entities within a game.
     */
    class Player : public ECS::Entity
    {
    public:
        /**
         * @brief Constructs a Player object.
         */
        Player();

        /**
         * @brief Destructor for cleaning up resources.
         */
        ~Player() = default;
    };
}
