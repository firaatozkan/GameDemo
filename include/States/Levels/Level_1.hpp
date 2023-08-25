#pragma once

#include "States/Levels/AbstractLevel.hpp"

class Level_1 : public AbstractLevel<Level_1>
{
private:
    friend class AbstractLevel<Level_1>;
    void initializeWorld();
    
public:
    Level_1(SDL_Renderer& rendererRef);
    ~Level_1() = default;
};