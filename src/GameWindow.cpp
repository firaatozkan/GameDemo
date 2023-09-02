#include <thread>
#include <stdexcept>
#include <SDL2/SDL.h>
#include "Core/GameWindow.hpp"
#include "States/Levels/Level_1.hpp"

using namespace Core;

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

    if (!SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED))
    {
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        throw std::runtime_error("Couldn't create renderer!");
    }
}

GameWindow::~GameWindow()
{
    SDL_DestroyRenderer(SDL_GetRenderer(m_window));
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

GameWindow& GameWindow::get()
{
    static GameWindow instance;
    return instance;
}

void GameWindow::run()
{
    m_currentState = std::make_unique<States::Levels::Level_1>();

    while (m_gameRunning)
    {
        const auto startTime = std::chrono::steady_clock::now();

        SDL_Event event;
        while (SDL_PollEvent(&event))
            m_currentState->handleInput(event);

        m_currentState->updateState(std::chrono::milliseconds(10));

        m_currentState->renderState();

        using namespace std::chrono_literals;

        const auto elapsed = std::chrono::steady_clock::now() - startTime;
        if (elapsed < 16.667ms)
            std::this_thread::sleep_for(16.667ms - elapsed);
    }
}

void GameWindow::quit()
{
    m_gameRunning = false;
}

SDL_Renderer* GameWindow::getRenderer() const
{
    return SDL_GetRenderer(m_window);
}