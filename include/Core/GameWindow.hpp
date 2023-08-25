#pragma once

#include <memory>

struct SDL_Window;
struct SDL_Renderer;

class AbstractState;

class GameWindow
{
public:
    GameWindow();
    ~GameWindow();
    void run();

private:
    SDL_Window* m_window {nullptr};
    SDL_Renderer* m_renderer {nullptr};

    bool m_gameRunning {true};
    std::unique_ptr<AbstractState> m_currentState;
};