/**
 * @file Vector2D.hpp
 * @brief Defines the Vector2D struct for representing 2D vectors.
 */

#pragma once

namespace Physics
{
    /**
     * @struct Vector2D
     * @brief Represents a 2D vector with X and Y components.
     *
     * The Vector2D struct is used to represent 2D vectors with X and Y components.
     * It is commonly used for specifying positions, directions, and velocities in
     * 2D space.
     */
    struct Vector2D
    {
        float X; /** The X-component of the 2D vector. */
        float Y; /** The Y-component of the 2D vector. */
    };
}
