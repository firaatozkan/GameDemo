#include "Core/Engine.hpp"
#include "Core/Camera.hpp"
#include "Interfaces/Entity.hpp"

namespace Core
{
    Camera::Camera()
    {
        m_view.setSize(1280, 720);
        m_view.setViewport({0.f, 0.f, 1.f, 1.f});
    }

    Camera& Camera::get()
    {
        static Camera instance;
        return instance;
    }

    void Camera::update(const Interfaces::Entity& entity)
    {
        auto newCenter = entity.getPosition();

        newCenter.x = std::clamp(newCenter.x, m_view.getSize().x / 2.f, Engine::WORLD_WIDTH - m_view.getSize().x / 2.f);
        newCenter.y = std::clamp(newCenter.y, m_view.getSize().y / 2.f, Engine::WORLD_HEIGHT - m_view.getSize().y / 2.f);

        m_view.setCenter(newCenter);
        Engine::get().renderer().setView(m_view);
    }
}