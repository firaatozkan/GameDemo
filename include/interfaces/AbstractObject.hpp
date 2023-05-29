#pragma once

struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Rect;

class AbstractObject
{
protected:
    SDL_Renderer &mRendererRef;
    SDL_Texture *mTexture{nullptr};
    SDL_Rect mSrcRect;
    SDL_Rect mDstRect;

public:
    AbstractObject(SDL_Renderer &rendererRef, const char *filename);
    virtual ~AbstractObject();
    virtual void Render() = 0;
    const SDL_Rect& GetRect() const;
    SDL_Rect& GetRect();
};