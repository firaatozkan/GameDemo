#pragma once

namespace Interfaces
{
    class GameObject
    {
    public:
        virtual ~GameObject() = default;
        virtual void draw() const = 0;
    };
}