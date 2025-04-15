#include <SFML/System.hpp>
#include "Assets/Player.hpp"

namespace Assets
{
    Player::Player(float x, float y)
        : Entity(Player::MASS)
    {
        m_position.x = x;
        m_position.y = y;

        m_animator.addAnimation("Idle", new Graphics::Animation(ASSETS_DIR "Swordsman/Idle.png", 8, 0.1f));
        m_animator.addAnimation("Walk", new Graphics::Animation(ASSETS_DIR "Swordsman/Walk.png", 8, 0.1f));
        m_animator.addAnimation("Run", new Graphics::Animation(ASSETS_DIR "Swordsman/Run.png", 8, 0.1f));
        m_animator.addAnimation("Jump", new Graphics::Animation(ASSETS_DIR "Swordsman/Jump.png", 8, 0.1f, true));
        m_animator.addAnimation("Hurt", new Graphics::Animation(ASSETS_DIR "Swordsman/Hurt.png", 3, 0.1f, true));
        m_animator.addAnimation("Attack1", new Graphics::Animation(ASSETS_DIR "Swordsman/Attack_3.png", {0.1f, 0.1f, 0.125f, 0.6f}, true));
        m_animator.addAnimation("Attack2", new Graphics::Animation(ASSETS_DIR "Swordsman/Attack_2.png", {0.1f, 0.24f, 0.6f}, true));
        m_animator.setCurrent("Idle");
    }

    sf::FloatRect Player::getBounds() const
    {
        if (m_animator.getCurrent() == "Attack1")
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
                m_velocity.x /= 6.f;
                m_animator.setCurrent("Attack1");
                break;

            case sf::Mouse::Right:
                m_velocity.x /= 6.f;
                m_animator.setCurrent("Attack2");
                break;

            default:
                break;
            }
        }

        if (input.type == sf::Event::KeyPressed)
        {
            switch (input.key.scancode)
            {
            case sf::Keyboard::W:
                if (m_onGround)
                {
                    m_velocity.y = -200.f;
                    m_animator.setCurrent("Jump");
                    m_onGround = false;
                }
                break;

            case sf::Keyboard::A:
                m_inputFlags |= Left;
                break;

            case sf::Keyboard::D:
                m_inputFlags |= Right;
                break;

            case sf::Keyboard::P:
                m_inputFlags |= Run;
                break;

            default:
                break;
            }
        }
        else if (input.type == sf::Event::KeyReleased)
        {
            switch (input.key.scancode)
            {
            case sf::Keyboard::A:
                m_inputFlags &= ~Left;
                break;

            case sf::Keyboard::D:
                m_inputFlags &= ~Right;
                break;

            case sf::Keyboard::P:
                m_inputFlags &= ~Run;
                break;
            }
        }
    }

    void Player::runAnimationLogic()
    {
        const auto& current = m_animator.getCurrent();
        const auto& currentAnim = m_animator.getCurrentAnimation();

        const bool stillAttacking = (current == "Attack1" || current == "Attack2") &&
                                    !currentAnim.isFinished();

        const bool stillJumping = (current == "Jump") &&
                                  !m_onGround;

        if (stillAttacking || stillJumping)
            return;

        const bool left = m_inputFlags & Left;
        const bool right = m_inputFlags & Right;
        const bool run = m_inputFlags & Run;

        if (left && !right)
        {
            m_velocity.x = run ? -240.f : -150.f;
            m_flipped = true;
            m_animator.setCurrent(run ? "Run" : "Walk");
        }
        else if (right && !left)
        {
            m_velocity.x = run ? 240.f : 150.f;
            m_flipped = false;
            m_animator.setCurrent(run ? "Run" : "Walk");
        }
        else if (m_onGround)
        {
            m_velocity.x = 0.f;
            m_animator.setCurrent("Idle");
        }
    }
}