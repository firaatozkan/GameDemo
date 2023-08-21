#pragma once

class IInputable
{
public:
    virtual ~IInputable() = default;
    virtual void handleInput(const SDL_Event& event);
};