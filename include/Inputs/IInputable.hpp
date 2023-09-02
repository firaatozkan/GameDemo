#pragma once

union SDL_Event;

namespace Inputs
{
    class IInputable
    {
    public:
        virtual ~IInputable() = default;
        virtual void handleInput(const SDL_Event& event) = 0;
    };
}