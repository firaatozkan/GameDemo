#pragma once

class IBody
{
public:
    virtual ~IBody() = default;
    virtual void applyPhysics(Uint32 deltaTime) = 0;
};