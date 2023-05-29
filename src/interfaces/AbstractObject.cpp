#include <future>
#include <SDL.h>
#include <SDL_image.h>
#include "interfaces/AbstractObject.hpp"

AbstractObject::AbstractObject(SDL_Renderer &rendererRef, const char *filename)
    : mRendererRef(rendererRef)
{
    mTexture = IMG_LoadTexture(&mRendererRef, filename);

    memset(&mDstRect, 0, sizeof(SDL_Rect));
    SDL_QueryTexture(mTexture, nullptr, nullptr, &mDstRect.w, &mDstRect.h);
    mSrcRect = mDstRect;
}

AbstractObject::~AbstractObject()
{
    SDL_DestroyTexture(mTexture);
}

const SDL_Rect& AbstractObject::GetRect() const
{
    return mDstRect;
}

SDL_Rect& AbstractObject::GetRect()
{
    return mDstRect;
}
