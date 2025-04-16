#pragma once

#include <memory>
#include <unordered_map>
#include <SFML/System.hpp>
#include "Interfaces/Entity.hpp"

namespace Assets
{
    class Player : public Interfaces::Entity
    {
    private:
        static constexpr float MASS = 40.0f;
        static constexpr float WALK_SPEED = 150.f;
        static constexpr float RUN_SPEED = WALK_SPEED * 1.6f;
        static constexpr float JUMP_SPEED = 200.f;
        static constexpr float ATTACK_SPEED_MULTIPLIER = 6.f; 

        enum InputFlags
        {
            None = 0,
            Left = 1 << 0,
            Right = 1 << 1,
            Run = 1 << 2,
            Jump = 1 << 3,
            Attack1 = 1 << 4,
            Attack2 = 1 << 5,
        };

    public:
        Player(float x = 0.f, float y = 0.f);

        ~Player() override = default;

        void handleInputs(const sf::Event& input);

    private:
        bool isAttacking() const;

        bool isJumping() const;

    protected:
        sf::FloatRect getBounds() const override;

        void runAnimationLogic() override;

    private:
        uint8_t m_inputFlags = None;
    };
}