#include <vector>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include "Graphics/Animation.hpp"

Animation::Animation(SDL_Renderer& rendererRef,
                     const char* filePath,
                     size_t maxNumOfFrames)
    : m_rendererRef(rendererRef),
      m_maxNumOfFrames(maxNumOfFrames)
{
    m_texture = IMG_LoadTexture(&m_rendererRef, filePath);

    SDL_Rect temp = {0, 0, 0, 0};
    SDL_QueryTexture(m_texture, nullptr, nullptr, &temp.w, &temp.h);

    for (size_t i = 0; i < m_maxNumOfFrames; ++i)
        m_frameVector.push_back(SDL_Rect{static_cast<int>(i) * (temp.w / static_cast<int>(m_maxNumOfFrames)),
                                         0,
                                         temp.w / static_cast<int>(m_maxNumOfFrames),
                                         temp.h});
}

Animation::~Animation()
{
    SDL_DestroyTexture(m_texture);
}

void Animation::renderAt(int x, int y, bool isFlipped)
{
    SDL_Rect dst = m_frameVector[0];

    dst.x = x;
    dst.y = y;

    SDL_RenderCopyEx(&m_rendererRef, m_texture, &m_frameVector[m_frameIndex], &dst, 0, nullptr, (isFlipped ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL));
}

void Animation::nextFrame()
{
    m_frameIndex = (m_frameIndex + 1) % m_maxNumOfFrames;
}

bool Animation::isFinished() const
{
    return m_frameIndex == m_maxNumOfFrames - 1;
}

void Animation::resetFrame()
{
    m_frameIndex = 0;
}