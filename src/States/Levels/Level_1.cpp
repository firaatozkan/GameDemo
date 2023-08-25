#include <iostream>
#include "States/Levels/Level_1.hpp"

class Demo : public BaseRenderableComponent
{
public:
    Demo(Entity& entityRef, SDL_Renderer& rendererRef) : BaseRenderableComponent(entityRef, rendererRef) {}

    void render() override
    {
        std::cout << "wow\n";
    }

    void bunu_da_deneyem()
    {
        std::cout << "pisirik\n";
    }
};

Level_1::Level_1(SDL_Renderer& rendererRef)
    : AbstractLevel(rendererRef)
{
}

void Level_1::initializeWorld()
{
    auto& player = m_world.createEntity();
    player.addComponent<Demo>(m_rendererRef);

    auto deneme = player.getComponent<Demo>();
}