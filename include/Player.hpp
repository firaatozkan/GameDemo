#pragma once

#include <memory>
#include <unordered_map>
#include <SFML/System.hpp>

#include "Entity.hpp"
#include "Animation.hpp"

class Player : public Entity
{
private:
    static constexpr float MASS = 40.0f;

public:
    Player(float x = 0.f, float y = 0.f);

    ~Player() = default;

    void handleInputs(const sf::Event& input);

    void applyCollision(Collidable& other) override;

    void update(float deltaTime) override;

    void draw() const override;

protected:
    sf::FloatRect getBounds() const override;

private:
    bool m_isFlipped {false};
    std::string m_currentAnimation;
    std::unordered_map<std::string, std::unique_ptr<Animation>> m_animations;
};