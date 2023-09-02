#pragma once

union SDL_Event;

namespace States
{
    class AbstractState
    {
    public:
        virtual ~AbstractState() = default;
        virtual void handleInput(const SDL_Event& event) = 0;
        virtual void updateState(const std::chrono::steady_clock::duration& deltaTime) = 0;
        virtual void renderState() = 0;
    };
}