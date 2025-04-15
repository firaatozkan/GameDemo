#include <SFML/System.hpp>
#include "Assets/Player.hpp"

namespace Assets
{
    Player::Player(float x, float y)
        : Entity(Player::MASS)
    {
        m_position.x = x;
        m_position.y = y;

        m_animator.addAnimation("Idle", new Graphics::Animation(R"(C:\Dev\GameDemo\assets\Swordsman\Idle.png)", 8, 0.1f));
        m_animator.addAnimation("Walk", new Graphics::Animation(R"(C:\Dev\GameDemo\assets\Swordsman\Walk.png)", 8, 0.1f));
        m_animator.addAnimation("Run", new Graphics::Animation(R"(C:\Dev\GameDemo\assets\Swordsman\Run.png)", 8, 0.1f));
        m_animator.addAnimation("Jump", new Graphics::Animation(R"(C:\Dev\GameDemo\assets\Swordsman\Jump.png)", 8, 0.1f, true));
        m_animator.addAnimation("Hurt", new Graphics::Animation(R"(C:\Dev\GameDemo\assets\Swordsman\Hurt.png)", 3, 0.1f, true));
        m_animator.addAnimation("Attack", new Graphics::Animation(R"(C:\Dev\GameDemo\assets\Swordsman\Attack_3.png)", {0.1f, 0.1f, 0.125f, 0.45f}, true));
        m_animator.setCurrent("Idle");
    }

    sf::FloatRect Player::getBounds() const
    {
        if (m_animator.getCurrent() == "Attack")
            return {m_position.x, m_position.y, 50, 128};

        return {m_position.x, m_position.y, 30, 128};
    }

    void Player::handleInputs(const sf::Event& input)
    {
        const auto& current = m_animator.getCurrent();

        if (input.type == sf::Event::MouseButtonPressed)
        {
            switch (input.mouseButton.button)
            {
            case sf::Mouse::Left:
                if (m_velocity.x != 0.f)
                    m_velocity.x /= 1.6f;

                m_animator.setCurrent("Attack");
                break;
            }
        }
        else if (input.type == sf::Event::KeyPressed)
        {
            switch (input.key.scancode)
            {
            case sf::Keyboard::W:
                m_velocity.y = -200.0f;
                m_animator.setCurrent("Jump");
                break;

            case sf::Keyboard::D:
                if (current != "Attack" &&
                    current != "Jump")
                {
                    m_velocity.x = 150.0f;
                    m_animator.setCurrent("Walk");
                }
                m_flipped = false;
                break;

            case sf::Keyboard::A:
                if (current != "Attack" &&
                    current != "Jump")
                {
                    m_velocity.x = -150.0f;
                    m_animator.setCurrent("Walk");
                }
                m_flipped = true;
                break;

            case sf::Keyboard::P:
                if (current == "Walk")
                {
                    m_velocity.x *= 1.6f;
                    m_animator.setCurrent("Run");
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
                if (current == "Run")
                {
                    m_velocity.x /= 1.6f;
                    m_animator.setCurrent("Walk");
                }
                break;

            case sf::Keyboard::A:
                [[fallthrough]];
            case sf::Keyboard::D:
                [[fallthrough]];
            default:
                if (current != "Jump")
                {
                    m_velocity.x = 0.f;
                    m_animator.setCurrent("Idle");
                }
                break;
            }
        }
    }

    void Player::runAnimationLogic()
    {
        if (m_animator.getCurrent() == "Attack" &&
            m_animator.getCurrentAnimation().isFinished())
        {
            m_velocity.x = 0.f;
            m_animator.setCurrent("Idle");
        }
        else if (m_animator.getCurrent() == "Jump" &&
                 m_animator.getCurrentAnimation().isFinished() &&
                 m_onGround)
        {
            m_velocity.x = 0.f;
            m_animator.setCurrent("Idle");
        }
    }
}