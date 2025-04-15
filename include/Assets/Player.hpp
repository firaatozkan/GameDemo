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

        enum InputFlags
        {
            None = 0,
            Left = 1 << 0,
            Right = 1 << 1,
            Run = 1 << 2,
        };

    public:
        Player(float x = 0.f, float y = 0.f);

        ~Player() override = default;

        void handleInputs(const sf::Event& input);

    protected:
        sf::FloatRect getBounds() const override;

        void runAnimationLogic() override;

    private:
        uint8_t m_inputFlags = None;
    };
}