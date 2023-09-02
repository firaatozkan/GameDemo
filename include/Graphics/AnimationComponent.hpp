#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include "ECS/Component.hpp"
#include "Physics/IUpdatable.hpp"
#include "Graphics/Animation.hpp"
#include "Graphics/IRenderable.hpp"

namespace Graphics
{
    class AnimationComponent : 
        public ECS::Component,
        public IRenderable,
        public Physics::IUpdatable
    {
    public:    
        AnimationComponent(ECS::Entity& entityRef,
                        const Animation::List& animationList,
                        const std::string& currentAnimation);
        ~AnimationComponent() = default;
        void render() override;
        void update(const std::chrono::steady_clock::duration& deltaTime) override;

        void setAnimation(const std::string& name);
        void flip(bool input);

    private:
        bool m_isFlipped {false};
        std::chrono::steady_clock::duration m_totalTime {0};
        std::string m_currentAnimation;
        std::unordered_map<std::string, std::unique_ptr<Animation>> m_animationMap;
    };
}