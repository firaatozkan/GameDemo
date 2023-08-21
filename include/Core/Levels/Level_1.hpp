#pragma once

class Level_1 : public BaseGameLevel<Level_1>
{
private:
    friend class BaseGameLevel<Level_1>;

    void initializeGameObjects();
    
public:
    Level_1(SDL_Renderer& rendererRef) : BaseGameLevel(rendererRef) {}
    ~Level_1() = default;

private:
    static constexpr Uint8 rgba_r = 50;
    static constexpr Uint8 rgba_g = 0;
    static constexpr Uint8 rgba_b = 0;
    static constexpr Uint8 rgba_a = 0;
};