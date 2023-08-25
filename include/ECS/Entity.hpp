#pragma once

class World;
class BaseComponent;
class BaseRenderableComponent;
class BaseUpdatableComponent;

class Entity
{
public:
    Entity(World& worldRef) : m_worldRef(worldRef) {}
    ~Entity() = default;

    template <typename T, typename... Args>
    std::enable_if_t<std::is_base_of_v<BaseComponent, T>, void> addComponent(Args&&... args)
    {
        auto component = std::make_unique<T>(*this, std::forward<Args>(args)...);

        if constexpr (std::is_base_of_v<BaseRenderableComponent, T>)
            m_worldRef.getRenderSystem().registerComponent(*this, std::move(component));

        else if constexpr (std::is_base_of_v<BaseUpdatableComponent, T>)
            m_worldRef.getUpdateSystem().registerComponent(*this, std::move(component));
            
    }

    template <typename T>
    std::enable_if_t<std::is_base_of_v<BaseComponent, T>, T*> getComponent()
    {
        if constexpr (std::is_base_of_v<BaseRenderableComponent, T>)
            return m_worldRef.getRenderSystem().lookupComponent<T>(*this);
            
        else if constexpr (std::is_base_of_v<BaseUpdatableComponent, T>)
            return m_worldRef.getUpdateSystem().lookupComponent<T>(*this);
    }

private:
    World& m_worldRef;
};