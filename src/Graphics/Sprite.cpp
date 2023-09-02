#include <SDL_image.h>
#include "Graphics/Sprite.hpp"
#include "Core/GameWindow.hpp"

using namespace Graphics;

Sprite::Sprite(const char* filename)
{
    m_texture = IMG_LoadTexture(Core::GameWindow::get().getRenderer(), filename);
    SDL_QueryTexture(m_texture, nullptr, nullptr, &m_srcRect.w, &m_srcRect.h);
}

Sprite::~Sprite()
{
    SDL_DestroyTexture(m_texture);
}

void Sprite::renderAt(float x, float y, bool flipped)
{
    SDL_Rect dstRect = m_srcRect;
    dstRect.x = static_cast<int>(x);
    dstRect.y = static_cast<int>(y);
    
    SDL_RenderCopyEx(Core::GameWindow::get().getRenderer(), m_texture, &m_srcRect, &dstRect, 0, nullptr, flipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}