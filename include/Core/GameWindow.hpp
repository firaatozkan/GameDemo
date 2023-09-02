/**
 * @file GameWindow.hpp
 * @brief Defines the GameWindow class for managing the game window and states.
 */

#pragma once

#include <memory>

struct SDL_Window;
struct SDL_Renderer;

namespace States
{
    class AbstractState;
}

namespace Core
{
    /**
     * @class GameWindow
     * @brief Manages the game window and states.
     *
     * The GameWindow class handles the creation and management of the game window,
     * as well as controlling the game loop and handling different states.
     */
    class GameWindow
    {
    private:
        /**
         * @brief Private constructor to enforce the singleton pattern.
         */
        GameWindow();

    public:
        /**
         * @brief Destructor for cleaning up resources.
         */
        ~GameWindow();

        /**
         * @brief Gets the singleton instance of GameWindow.
         * @return Reference to the GameWindow instance.
         */
        static GameWindow& get();

        /**
         * @brief Runs the game loop.
         */
        void run();

        /**
         * @brief Quits the game.
         */
        void quit();

        /**
         * @brief Gets the SDL_Renderer associated with the game window.
         * @return Pointer to the SDL_Renderer.
         */
        SDL_Renderer* getRenderer() const;

    private:
        SDL_Window* m_window {nullptr}; /** Pointer to the SDL window. */

        bool m_gameRunning {true}; /** Flag indicating if the game is running. */
        std::unique_ptr<States::AbstractState> m_currentState; /** Current game state. */
    };
}
