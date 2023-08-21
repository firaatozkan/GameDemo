#pragma once

struct SDL_Window;
struct SDL_Renderer;

class AbstractGameState;

class GameWindow
{
public:
    GameWindow();
    ~GameWindow();
    void run();

private:
    SDL_Window* m_window {nullptr};
    SDL_Renderer* m_renderer {nullptr};

    bool m_gameRunning {false};
    
    AbstractGameState* m_currentState {nullptr};
};