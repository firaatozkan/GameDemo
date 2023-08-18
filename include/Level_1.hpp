#pragma once

#include <vector>

class IRenderable;
class IUpdatable;
class Player;

class Level_1 : public AbstractGameState
{
public:
    Level_1(SDL_Renderer& rendererRef);
    ~Level_1();
    void handleInput(const SDL_Event& input, bool& gameRunningFlag) override;
    void renderObjects(void) override;
    void updateState(unsigned int deltaTime) override;

private:
    Player* m_player {nullptr};
    std::vector<IRenderable*> m_renderableVector;
    std::vector<IUpdatable*> m_updatableVector;
};