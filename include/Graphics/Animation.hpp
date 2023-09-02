#pragma once

#include <tuple>
#include <string>
#include <initializer_list>
#include "Graphics/Sprite.hpp"

namespace Graphics
{
    class Animation : public Sprite
    {
    public:
        using List = std::initializer_list<std::pair<std::string, Animation*>>;

        Animation(const char* filename, int frameCount);
        ~Animation() = default;
        void nextFrame();
        void resetFrame();
        
    private:
        int m_frameCount;
    };
}