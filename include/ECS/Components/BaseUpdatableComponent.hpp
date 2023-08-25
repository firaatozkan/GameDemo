#pragma once

#include "ECS/Components/BaseComponent.hpp"

class BaseUpdatableComponent : public BaseComponent
{
public:
    BaseUpdatableComponent(Entity& entityRef) : BaseComponent(entityRef) {}
    virtual ~BaseUpdatableComponent() = default;
    virtual void update(unsigned int deltaTime) = 0;
};