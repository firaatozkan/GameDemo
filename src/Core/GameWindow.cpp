#include <chrono>
#include <stdexcept>
#include <SDL2/SDL.h>
#include "Core/GameWindow.hpp"
#include "Core/AbstractGameState.hpp"
#include "Core/Level_1.hpp"

GameWindow::GameWindow()
{
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
        throw std::runtime_error("Couldn't initialize SDL!");

    m_window = SDL_CreateWindow("Main Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,800, 600, SDL_WINDOW_SHOWN);
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
}

GameWindow::~GameWindow()
{
    if (m_currentState)
        delete m_currentState;

    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void GameWindow::run()
{
    m_gameRunning = true;

    SDL_Event event;

    m_currentState = new Level_1(*m_renderer);

    Uint32 startTime = SDL_GetTicks();
    Uint32 endTime;
    Uint32 deltaTime;

    while (m_gameRunning)
    {
        endTime = SDL_GetTicks();
        deltaTime = endTime - startTime;
        startTime = SDL_GetTicks();

        while (SDL_PollEvent(&event))
            m_currentState->handleInput(event, m_gameRunning);

        m_currentState->updateState(deltaTime);

        m_currentState->renderObjects();

        if (deltaTime < 1000 / 60)
            SDL_Delay((1000 / 60) - deltaTime);
    }
}