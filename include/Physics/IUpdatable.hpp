#pragma once

#include <chrono>

namespace Physics
{
    class IUpdatable
    {
    public:
        virtual ~IUpdatable() = default;
        virtual void update(const std::chrono::steady_clock::duration& deltaTime) = 0;
    };
}