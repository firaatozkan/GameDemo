#pragma once

#include "ECS/Components/BaseComponent.hpp"

class BaseInputController : public BaseComponent
{
public:
    BaseInputController(Entity& entityRef) : BaseComponent(entityRef) {}
    virtual ~BaseInputController() = default;
    virtual void handleInput(const SDL_Event& event) = 0;
};