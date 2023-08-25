#pragma once

#include <memory>
#include <typeindex>
#include <unordered_map>
#include "ECS/Components/BaseInputController.hpp"
#include "ECS/Components/BaseRenderableComponent.hpp"
#include "ECS/Components/BaseUpdatableComponent.hpp"

template <typename T>
class GenericSystem
{
public:
    GenericSystem() = default;
    ~GenericSystem() = default;

    template <typename... Args>
    void runSystem(Args&&... args);

    template <typename C>
    std::enable_if_t<std::is_base_of_v<T, C>, void> registerComponent(Entity& entityRef, std::unique_ptr<C> component)
    {
        m_componentMap[&entityRef][typeid(T)] = std::move(component);
    }
    
    template <typename C>
    std::enable_if_t<std::is_base_of_v<T, C>, C*> lookupComponent(Entity& entityRef)
    {
        return reinterpret_cast<C*>(m_componentMap[&entityRef][typeid(T)].get());
    }

private:
    std::unordered_map<Entity*, std::unordered_map<std::type_index, std::unique_ptr<T>>> m_componentMap;
};

template <>
template <typename... Args>
void GenericSystem<BaseInputController>::runSystem(Args&&... args)
{
    for (auto& [_, components] : m_componentMap)
        for (auto& [__, component] : components)
            component->handleInput(std::forward<Args>(args)...);
}

template <>
template <typename... Args>
void GenericSystem<BaseRenderableComponent>::runSystem(Args&&... args)
{
    for (auto& [_, components] : m_componentMap)
        for (auto& [__, component] : components)
            component->render();
}

template <>
template <typename... Args>
void GenericSystem<BaseUpdatableComponent>::runSystem(Args&&... args)
{
    for (auto& [_, components] : m_componentMap)
        for (auto& [__, component] : components)
            component->update(std::forward<Args>(args)...);
}

using RenderSystem = GenericSystem<BaseRenderableComponent>;
using UpdateSystem = GenericSystem<BaseUpdatableComponent>;
using InputSystem = GenericSystem<BaseInputController>;
