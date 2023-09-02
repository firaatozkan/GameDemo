#pragma once

#include <SDL2/SDL.h>

namespace Graphics
{
    class Sprite
    {
    public:
        Sprite(const char* filename);
        virtual ~Sprite();
        void renderAt(float x, float y, bool flipped);

    private:
        SDL_Texture* m_texture {nullptr};

    protected:
        SDL_Rect m_srcRect {0, 0, 0, 0};
    };
}