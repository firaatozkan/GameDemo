#include <stdexcept>
#include <SDL2/SDL.h>
#include "Core/GameWindow.hpp"
#include "States/Levels/Level_1.hpp"

GameWindow::GameWindow()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        throw std::runtime_error("Couldn't initialize SDL!");

    m_window = SDL_CreateWindow("Game",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                800,
                                600,
                                SDL_WINDOW_SHOWN);

    if (!m_window)
    {
        SDL_Quit();
        throw std::runtime_error("Couldn't create window!");
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    if (!m_renderer)
    {
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        throw std::runtime_error("Couldn't create renderer!");
    }

    m_currentState = std::make_unique<Level_1>(*m_renderer);
}

GameWindow::~GameWindow()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void GameWindow::run()
{
    unsigned int startTime = SDL_GetTicks();
    unsigned int deltaTime;

    SDL_Event event;

    while (m_gameRunning)
    {
        while (SDL_PollEvent(&event))
            m_currentState->handleInput(event);

        deltaTime = SDL_GetTicks() - startTime;
        startTime = SDL_GetTicks();

        m_currentState->updateState(deltaTime);

        m_currentState->renderState();

        if (deltaTime < (1000 / 60))
            SDL_Delay((1000 / 60) - deltaTime);
    }
}