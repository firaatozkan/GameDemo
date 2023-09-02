/**
 * @file Sprite.hpp
 * @brief Defines the Sprite class for rendering images.
 */

#pragma once

#include <SDL2/SDL.h>

namespace Graphics
{
    /**
     * @class Sprite
     * @brief Represents a 2D image for rendering.
     *
     * The Sprite class encapsulates functionality for rendering 2D images
     * onto the screen, including the ability to specify position and flip the image.
     */
    class Sprite
    {
    public:
        /**
         * @brief Constructs a Sprite object from a file.
         *
         * @param filename The filename of the image to load as a sprite.
         */
        Sprite(const char* filename);

        /**
         * @brief Virtual destructor for cleaning up resources.
         */
        virtual ~Sprite();

        /**
         * @brief Renders the sprite at a specified position.
         *
         * @param x The X-coordinate where the sprite will be rendered.
         * @param y The Y-coordinate where the sprite will be rendered.
         * @param flipped Indicates whether the sprite should be horizontally flipped.
         */
        void renderAt(float x, float y, bool flipped);

    private:
        SDL_Texture* m_texture {nullptr}; /**< Pointer to the SDL texture for the sprite image. */

    protected:
        SDL_Rect m_srcRect {0, 0, 0, 0}; /**< Source rectangle for rendering a portion of the sprite image. */
    };
}
