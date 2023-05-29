#pragma once

struct SDL_Renderer;
union SDL_Event;

class BaseGame;
class AbstractObject;
class RenderPool;

class AbstractLevel
{
    std::vector<AbstractObject *> mLevelObjects;

protected:
    BaseGame &mParentGameRef;
    SDL_Renderer &mRendererRef;
    
    void AddObject(AbstractObject* object);

public:
    AbstractLevel(BaseGame &parentGameRef);
    virtual ~AbstractLevel();
    void RenderObjects(RenderPool& renderPool);
    virtual void HandleEvent(SDL_Event& event, bool& gameRunningFlag) = 0;
    virtual void RunGameLogic() = 0;
};