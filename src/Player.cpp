#include <iostream>
#include "Player.hpp"
#include <SFML/System.hpp>

Player::Player(float x, float y)
    : Entity(Player::MASS)
{
    m_position.x = x;
    m_position.y = y;

    m_animations.emplace("idle", new Animation(R"(C:\Dev\GameDemo\assets\Swordsman\Idle.png)", 8, 0.1f));
    m_animations.emplace("walk", new Animation(R"(C:\Dev\GameDemo\assets\Swordsman\Walk.png)", 8, 0.1f));
    m_animations.emplace("run", new Animation(R"(C:\Dev\GameDemo\assets\Swordsman\Run.png)", 8, 0.1f));
    m_animations.emplace("jump", new Animation(R"(C:\Dev\GameDemo\assets\Swordsman\Jump.png)", 8, 0.1f, true));
    m_animations.emplace("hurt", new Animation(R"(C:\Dev\GameDemo\assets\Swordsman\Hurt.png)", 3, 0.1f, true));
    m_animations.emplace("attack", new Animation(R"(C:\Dev\GameDemo\assets\Swordsman\Attack_3.png)", {0.1f, 0.1f, 0.125f, 0.45f}, true));

    m_currentAnimation = "idle";
}

sf::FloatRect Player::getBounds() const
{
    if (m_currentAnimation == "attack")
        return {m_position.x, m_position.y, 50, 128};

    return {m_position.x, m_position.y, 30, 128};
}

void Player::handleInputs(const sf::Event& input)
{
    if (input.type == sf::Event::MouseButtonPressed)
    {
        switch (input.mouseButton.button)
        {
        case sf::Mouse::Left:
            if (m_currentAnimation != "jump")
            {
                m_currentAnimation = "attack";
                m_animations[m_currentAnimation]->resetAnimation();
            }
            break;
        }
    }
    else if (input.type == sf::Event::MouseButtonReleased)
    {

    }
    else if (input.type == sf::Event::KeyPressed)
    {
        switch (input.key.scancode)
        {
        case sf::Keyboard::W:
            if (m_currentAnimation != "jump")
            {
                m_velocity.y = -200.0f;
                m_currentAnimation = "jump";
                m_animations[m_currentAnimation]->resetAnimation();
            }
            break;

        case sf::Keyboard::D:
            if (m_currentAnimation != "attack")
            {
                m_currentAnimation = "walk";
                m_velocity.x = 150.0f;
            }
            m_isFlipped = false;
            break;

        case sf::Keyboard::A:
            if (m_currentAnimation != "attack")
            {
                m_currentAnimation = "walk";
                m_velocity.x = -150.0f;
            }
            m_isFlipped = true;
            break;

        case sf::Keyboard::P:
            if (m_currentAnimation == "walk")
            {
                m_currentAnimation = "run";
                m_velocity.x *= 1.6f;
            }
            break;

        default:
            break;
        }
    }
    else if (input.type == sf::Event::KeyReleased)
    {
        switch (input.key.scancode)
        {
        case sf::Keyboard::P:
            if (m_currentAnimation == "run")
            {
                m_currentAnimation = "walk";
                m_velocity.x /= 1.6f;
            }
            break;

        case sf::Keyboard::A:
            [[fallthrough]];
        case sf::Keyboard::D:
            [[fallthrough]];
        default:
            if (m_currentAnimation != "jump")
            {
                m_velocity.x = 0;
                m_currentAnimation = "idle";
            }
            break;
        }
    }
}

void Player::applyCollision(Collidable& other)
{
    this->Entity::applyCollision(other);

    auto player = dynamic_cast<Player*>(&other);

    if (!player)
        return;

    if (m_currentAnimation == "attack")
    {
        player->m_currentAnimation = "hurt";
        player->m_animations[player->m_currentAnimation]->resetAnimation();
    }
}

void Player::update(float deltaTime)
{
    const bool isGrounded = m_isGrounded;

    this->Entity::update(deltaTime);

    if (m_currentAnimation == "jump" && isGrounded)
    {
        m_velocity.x = 0;
        m_currentAnimation = "idle";
        m_animations[m_currentAnimation]->resetAnimation();
    }
    else if (m_currentAnimation == "attack" &&
             m_animations[m_currentAnimation]->isFinished())
    {
        m_currentAnimation = "idle";
        m_animations[m_currentAnimation]->resetAnimation();
    }
    else if (m_currentAnimation == "hurt" &&
             m_animations[m_currentAnimation]->isFinished())
    {
        m_currentAnimation = "idle";
        m_animations[m_currentAnimation]->resetAnimation();
    }

    m_animations[m_currentAnimation]->update(deltaTime);
}

void Player::draw() const
{
    m_animations.at(m_currentAnimation)->draw(m_position, m_isFlipped);
}