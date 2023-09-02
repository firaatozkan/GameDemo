#pragma once

#include "States/Levels/AbstractLevel.hpp"

namespace States::Levels
{
    class Level_1 : public AbstractLevel<Level_1>
    {
    private:
        friend class AbstractLevel<Level_1>;
        
        static constexpr int color_red = 108;
        static constexpr int color_green = 145;
        static constexpr int color_blue = 144;
        static constexpr int color_alpha = 0;

        void initializeLevel();
        
    public:
        Level_1() = default;
        ~Level_1() = default;
    };
}