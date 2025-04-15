#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include "Graphics/Animation.hpp"

namespace Graphics
{
    class Animator
    {
    public:
        void setCurrent(const std::string& name);

        const std::string& getCurrent() const;

        void addAnimation(const std::string& name, Animation* anim);

        const Animation& getCurrentAnimation() const;

        void update(float deltaTime);

        void draw(const sf::Vector2f& position, bool flip) const;

    private:
        std::string m_current;
        std::unordered_map<std::string, std::unique_ptr<Animation>> m_animations;
    };
}