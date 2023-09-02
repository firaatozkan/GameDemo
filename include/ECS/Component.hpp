#pragma once

namespace ECS
{
    class Entity;

    class Component
    {
    public:
        Component(Entity& entityRef) : m_entityRef(entityRef) {}
        virtual ~Component() = default;

    protected:
        Entity& m_entityRef;
    };
}