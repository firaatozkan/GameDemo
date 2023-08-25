#pragma once

class Entity;

class BaseComponent
{
public:
    BaseComponent(Entity& entityRef) : m_entityRef(entityRef) {}
    virtual ~BaseComponent() = default;

protected:
    Entity& m_entityRef;
};