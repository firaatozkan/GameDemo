#pragma once

class IUpdatable
{
public:
    virtual ~IUpdatable() = default;
    virtual void update(unsigned int deltaTime) = 0;
};