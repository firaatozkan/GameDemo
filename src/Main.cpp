/**
 * @file main.cpp
 * @brief Entry point for the game application.
 */

#include "Core/GameWindow.hpp"

/**
 * @brief The entry point of the game application.
 *
 * The main function initializes the game window and starts the game loop by calling
 * the run method of the GameWindow singleton instance.
 *
 * @return The exit code of the application.
 */
int main()
{
    // Initialize the game window and start the game loop.
    Core::GameWindow::get().run();

    // The game loop handles the application's execution, so no further code execution occurs here.

    return 0; // Return an exit code (0 for success).
}
