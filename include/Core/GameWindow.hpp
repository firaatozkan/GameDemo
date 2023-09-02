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
    class GameWindow
    {
    private:
        GameWindow();
    public:
        ~GameWindow();
        static GameWindow& get();
        void run();

        void quit();
        SDL_Renderer* getRenderer() const;

    private:
        SDL_Window* m_window {nullptr};

        bool m_gameRunning {true};
        std::unique_ptr<States::AbstractState> m_currentState;
    };
}