#pragma once

#include <memory>
#include <typeindex>
#include <unordered_map>

namespace ECS
{
    class Component;

    class Entity
    {
    public:
        Entity() = default;
        virtual ~Entity() = default;

        template <typename T, typename... Args, typename = std::enable_if_t<std::is_base_of_v<Component, T>>>
        T& addComponent(Args&&... args)
        {
            m_componentMap.emplace(typeid(T), std::make_unique<T>(*this, std::forward<Args>(args)...));
            return *(reinterpret_cast<T*>(m_componentMap[typeid(T)].get()));
        }
        
        template <typename T, typename = std::enable_if_t<std::is_base_of_v<Component, T>>>
        T& getComponent()
        {
            return *(reinterpret_cast<T*>(m_componentMap[typeid(T)].get()));
        }

        std::unordered_map<std::type_index, std::unique_ptr<Component>>& getComponentMap() { return m_componentMap; }
        const std::unordered_map<std::type_index, std::unique_ptr<Component>>& getComponentMap() const{ return m_componentMap; }

    private:
        std::unordered_map<std::type_index, std::unique_ptr<Component>> m_componentMap;
    };
}