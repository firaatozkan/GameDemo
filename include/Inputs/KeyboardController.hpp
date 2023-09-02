#pragma once

#include "ECS/Component.hpp"
#include "Inputs/IInputable.hpp"

namespace Inputs
{
    class KeyboardController : 
        public ECS::Component,
        public IInputable
    {
    public:
        KeyboardController(ECS::Entity& entityRef);
        ~KeyboardController() = default;
        void handleInput(const SDL_Event& event) override;
    };
}