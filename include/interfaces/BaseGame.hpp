#pragma once

struct SDL_Window;
struct SDL_Renderer;

class AbstractLevel;

class BaseGame
{
    unsigned int mTargetFps;
    SDL_Window *mWindow{nullptr};
    std::vector<AbstractLevel *> mLevelVec;
    std::vector<AbstractLevel *>::iterator mCurrentLevel;

protected:
    SDL_Renderer *mRenderer{nullptr};

protected:
    void AddLevel(AbstractLevel *level);

public:
    BaseGame(const char *title, int w, int h, unsigned int targetFps);
    virtual ~BaseGame();
    void Run();
    SDL_Renderer &GetRenderer();
    const SDL_Renderer &GetRenderer() const;
    void NextLevel();
    void PrevLevel();
};