#include "Graphics/Animation.hpp"

using namespace Graphics;

Animation::Animation(const char* filename, int frameCount) :
    Sprite(filename),
    m_frameCount(frameCount)
{
    m_srcRect.w /= m_frameCount;
}

void Animation::nextFrame()
{
    m_srcRect.x = (m_srcRect.x + m_srcRect.w) % (m_srcRect.w * m_frameCount);
}

void Animation::resetFrame()
{
    m_srcRect.x = 0;
}