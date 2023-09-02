/**
 * @file Animation.hpp
 * @brief Defines the Animation class for sprite animations.
 */

#pragma once

#include <tuple>
#include <string>
#include <initializer_list>
#include "Graphics/Sprite.hpp"

namespace Graphics
{
    /**
     * @class Animation
     * @brief Represents a sprite animation.
     *
     * The Animation class extends the Sprite class and provides functionality
     * for managing sprite animations, including switching between frames.
     */
    class Animation : public Sprite
    {
    public:
        /**
         * @brief Defines a list of sprite animations.
         *
         * The List type is an initializer list of pairs, where each pair consists
         * of a string identifier and a pointer to an Animation object.
         */
        using List = std::initializer_list<std::pair<std::string, Animation*>>;

        /**
         * @brief Constructs an Animation object.
         *
         * @param filename The filename of the sprite image.
         * @param frameCount The number of frames in the animation.
         */
        Animation(const char* filename, int frameCount);

        /**
         * @brief Destructor for cleaning up resources.
         */
        ~Animation() = default;

        /**
         * @brief Advances to the next frame of the animation.
         */
        void nextFrame();

        /**
         * @brief Resets the animation to the first frame.
         */
        void resetFrame();

    private:
        int m_frameCount; /**< The total number of frames in the animation. */
    };
}
