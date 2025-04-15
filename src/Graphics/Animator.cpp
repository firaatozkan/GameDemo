#include "Graphics/Animator.hpp"

namespace Graphics
{
    void Animator::setCurrent(const std::string& name)
    {
        if (m_current != name)
        {
            m_current = name;
            m_animations[m_current]->resetAnimation();
        }
    }

    const std::string& Animator::getCurrent() const
    {
        return m_current;
    }

    void Animator::addAnimation(const std::string& name, Animation* anim)
    {
        m_animations.emplace(name, anim);
    }

    const Animation& Animator::getCurrentAnimation() const
    {
        return* m_animations.at(m_current);
    }

    void Animator::update(float deltaTime)
    {
        m_animations[m_current]->update(deltaTime);
    }

    void Animator::draw(const sf::Vector2f& position, bool flip) const
    {
        m_animations.at(m_current)->draw(position, flip);
    }
}