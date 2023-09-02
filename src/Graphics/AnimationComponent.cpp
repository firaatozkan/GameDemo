#include "ECS/Entity.hpp"
#include "Physics/TransformComponent.hpp"
#include "Graphics/AnimationComponent.hpp"

using namespace Graphics;

AnimationComponent::AnimationComponent(ECS::Entity& entityRef,
                                       const Animation::List& animationList,
                                       const std::string& currentAnimation) :
    ECS::Component(entityRef),
    m_currentAnimation(currentAnimation)
{
    for (const auto& animation : animationList)
        m_animationMap.emplace(animation.first, animation.second);
}

void AnimationComponent::render()
{
    m_animationMap[m_currentAnimation]->renderAt(m_entityRef.getComponent<Physics::TransformComponent>().getPositionX(),
                                                 m_entityRef.getComponent<Physics::TransformComponent>().getPositionY(),
                                                 m_isFlipped);
}

void AnimationComponent::update(const std::chrono::steady_clock::duration& deltaTime)
{
    m_totalTime += deltaTime;

    using namespace std::chrono_literals;

    if (m_totalTime > 60ms)
    {
        m_animationMap[m_currentAnimation]->nextFrame();
        m_totalTime = 0ns;
    }
}

void AnimationComponent::setAnimation(const std::string& name)
{
    m_currentAnimation = name;
}

void AnimationComponent::flip(bool input)
{
    m_isFlipped = input;
}