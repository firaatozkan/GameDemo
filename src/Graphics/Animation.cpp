/**
 * @file Animation.cpp
 * @brief Implements the Animation class for sprite animations.
 */

#include "Graphics/Animation.hpp"

using namespace Graphics;

/**
 * @brief Constructs an Animation object with a sprite sheet and frame count.
 *
 * The constructor initializes an Animation object with a specified sprite sheet
 * and the number of frames in the animation.
 *
 * @param filename The filename of the sprite sheet.
 * @param frameCount The number of frames in the animation.
 */
Animation::Animation(const char* filename, int frameCount) :
    Sprite(filename), /**< Initialize the base class Sprite with the sprite sheet filename. */
    m_frameCount(frameCount) /**< Initialize the frame count. */
{
    // Calculate the width of each frame based on the sprite sheet width and frame count.
    m_srcRect.w /= m_frameCount;
}

/**
 * @brief Advances the animation to the next frame.
 *
 * The nextFrame method updates the source rectangle's X-coordinate to move to the
 * next frame in the animation sequence. It handles looping back to the first frame
 * if the end of the animation is reached.
 */
void Animation::nextFrame()
{
    // Update the source rectangle's X-coordinate to move to the next frame.
    m_srcRect.x = (m_srcRect.x + m_srcRect.w) % (m_srcRect.w * m_frameCount);
}

/**
 * @brief Resets the animation to the first frame.
 *
 * The resetFrame method sets the source rectangle's X-coordinate back to the
 * starting position, effectively resetting the animation to the first frame.
 */
void Animation::resetFrame()
{
    // Reset the source rectangle's X-coordinate to the starting position.
    m_srcRect.x = 0;
}
