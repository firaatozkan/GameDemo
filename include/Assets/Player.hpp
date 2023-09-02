#pragma once

#include "ECS/Entity.hpp"

namespace Assets
{
    class Player : public ECS::Entity
    {
    public:
        Player();
        ~Player() = default;
    };
}