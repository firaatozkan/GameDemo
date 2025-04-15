#pragma once

namespace Interfaces
{
    class Scene
    {
    public:
        virtual ~Scene() = default;

        virtual void handleEvents() = 0;

        virtual void update(float dt) = 0;

        virtual sf::Color getBackgroundColor() const = 0;

        virtual void draw() const = 0;
    };
}