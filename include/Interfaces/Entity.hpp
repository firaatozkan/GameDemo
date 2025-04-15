#pragma once

#include <SFML/System.hpp>
#include "Graphics/Animator.hpp"
#include "Interfaces/CollidableObject.hpp"

namespace Assets
{
    class TileMap;
}

namespace Interfaces
{
    class Entity : public CollidableObject
    {
    public:
        friend class Assets::TileMap;

        explicit Entity(float mass);

        ~Entity() override = default;

        void updateVelocity(float deltaTime);

        void applyCollision(CollidableObject& other,
                            const sf::FloatRect& intersection) override;

        void updatePosition(float deltaTime);

        void updateAnimation(float deltaTime);

        void draw() const override;

        void setOnGround();

        sf::Vector2f& getPosition();

        const sf::Vector2f& getPosition() const;

        sf::Vector2f& getVelocity();

        const sf::Vector2f& getVelocity() const;

    protected:
        virtual void runAnimationLogic() = 0;

        const float m_mass;
        bool m_flipped{false};
        bool m_onGround{false};

        sf::Vector2f m_position;
        sf::Vector2f m_velocity;

        Graphics::Animator m_animator;
    };
}