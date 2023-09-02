/**
 * @file Sprite.cpp
 * @brief Implements the Sprite class for rendering images.
 */

#include <SDL_image.h>
#include "Graphics/Sprite.hpp"
#include "Core/GameWindow.hpp"

using namespace Graphics;

/**
 * @brief Constructs a Sprite from an image file.
 *
 * The constructor initializes a Sprite by loading an image from the specified file.
 *
 * @param filename The filename of the image to load as a texture.
 */
Sprite::Sprite(const char* filename)
{
    // Load the image as a texture using the game window's renderer.
    m_texture = IMG_LoadTexture(Core::GameWindow::get().getRenderer(), filename);

    // Query the texture to determine its width and height.
    SDL_QueryTexture(m_texture, nullptr, nullptr, &m_srcRect.w, &m_srcRect.h);
}

/**
 * @brief Destructor for cleaning up resources.
 *
 * The destructor releases the texture resource when the Sprite is destroyed.
 */
Sprite::~Sprite()
{
    SDL_DestroyTexture(m_texture);
}

/**
 * @brief Renders the sprite at a specified position with optional horizontal flip.
 *
 * The renderAt method renders the sprite at the specified (x, y) position on the screen,
 * allowing for horizontal flipping if needed.
 *
 * @param x The X-coordinate to render the sprite.
 * @param y The Y-coordinate to render the sprite.
 * @param flipped A boolean indicating whether to horizontally flip the sprite.
 */
void Sprite::renderAt(float x, float y, bool flipped)
{
    SDL_Rect dstRect = m_srcRect;
    dstRect.x = static_cast<int>(x);
    dstRect.y = static_cast<int>(y);

    // Render the texture with optional horizontal flip using the game window's renderer.
    SDL_RenderCopyEx(Core::GameWindow::get().getRenderer(), m_texture, &m_srcRect, &dstRect, 0, nullptr, flipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}
