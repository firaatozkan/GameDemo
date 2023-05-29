#include <vector>
#include <stdexcept>
#include <queue>
#include <mutex>
#include <future>
#include <condition_variable>
#include <SDL.h>
#include <SDL_image.h>
#include "utils/RenderPool.hpp"
#include "interfaces/AbstractLevel.hpp"
#include "interfaces/AbstractObject.hpp"
#include "interfaces/BaseGame.hpp"

BaseGame::BaseGame(const char *title, int w, int h, unsigned int targetFps)
    : mTargetFps(targetFps)
{
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0)
        throw std::runtime_error("Couldn't initialize SDL!");

    mWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
    if (!mWindow)
        throw std::runtime_error("Couldn't create window!");

    mRenderer = SDL_CreateRenderer(mWindow, 0, 0);
    if (!mRenderer)
        throw std::runtime_error("Couldn't create renderer!");
}

BaseGame::~BaseGame()
{
    for (auto level : mLevelVec)
        delete level;

    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
}

void BaseGame::Run()
{
    const auto FRAME_DELAY = 1000 / mTargetFps;
    SDL_Event event;
    RenderPool renderPool;

    mCurrentLevel = mLevelVec.begin();

    bool gameRunning = true;

    Uint32 frameStart, frameElapsed;
    while (gameRunning)
    {
        frameStart = SDL_GetTicks();

        while (SDL_PollEvent(&event))
            (*mCurrentLevel)->HandleEvent(event, gameRunning);

        SDL_RenderClear(mRenderer);
        (*mCurrentLevel)->RenderObjects(renderPool);
        SDL_RenderPresent(mRenderer);

        frameElapsed = SDL_GetTicks() - frameStart;
        if (FRAME_DELAY > frameElapsed)
            SDL_Delay(FRAME_DELAY - frameElapsed);
    }
}

void BaseGame::AddLevel(AbstractLevel* level)
{
    mLevelVec.push_back(level);
}

SDL_Renderer& BaseGame::GetRenderer()
{
    return *mRenderer;
}

const SDL_Renderer& BaseGame::GetRenderer() const
{
    return *mRenderer;
}

void BaseGame::NextLevel()
{
    ++mCurrentLevel;    
}

void BaseGame::PrevLevel()
{
    --mCurrentLevel;
}
