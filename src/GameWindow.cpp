/**
 * @file GameWindow.cpp
 * @brief Implements the GameWindow class for managing the game window and loop.
 */

#include <thread>
#include <stdexcept>
#include <SDL2/SDL.h>
#include "Core/GameWindow.hpp"
#include "States/Levels/Level_1.hpp"

using namespace Core;

/**
 * @brief Constructs a GameWindow and initializes SDL components.
 *
 * The constructor initializes SDL components, including the window and renderer.
 * It also sets up the initial game state.
 */
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

/**
 * @brief Destructs the GameWindow and cleans up SDL resources.
 *
 * The destructor cleans up SDL resources, including the window and renderer.
 */
GameWindow::~GameWindow()
{
    SDL_DestroyRenderer(SDL_GetRenderer(m_window));
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

/**
 * @brief Gets a reference to the GameWindow instance.
 *
 * The get method provides access to the singleton instance of the GameWindow class.
 *
 * @return A reference to the GameWindow instance.
 */
GameWindow& GameWindow::get()
{
    static GameWindow instance;
    return instance;
}

/**
 * @brief Runs the game loop.
 *
 * The run method starts the game loop, handling events, updating the current game state,
 * and rendering frames. It also includes frame rate limiting.
 */
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

/**
 * @brief Signals the game to quit.
 *
 * The quit method sets the gameRunning flag to false, which will terminate the game loop.
 */
void GameWindow::quit()
{
    m_gameRunning = false;
}

/**
 * @brief Gets the SDL renderer associated with the game window.
 *
 * The getRenderer method returns a pointer to the SDL renderer used for rendering graphics.
 *
 * @return A pointer to the SDL renderer.
 */
SDL_Renderer* GameWindow::getRenderer() const
{
    return SDL_GetRenderer(m_window);
}
