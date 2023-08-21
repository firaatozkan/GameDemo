#pragma once

class ICollidable
{
public:
    virtual ~ICollidable() = default;
    virtual bool doesCollideWith(ICollidable* other) = 0;
    virtual void applyCollision(ICollidable* other) = 0;
};