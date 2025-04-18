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
        m_animator.addAnimation("Attack1", new Graphics::Animation(ASSETS_DIR "Swordsman/Attack_3.png", {0.1f, 0.1f, 0.1f, 0.6f}, true));
        m_animator.addAnimation("Attack2", new Graphics::Animation(ASSETS_DIR "Swordsman/Attack_2.png", {0.1f, 0.1f, 0.6f}, true));
        m_animator.addAnimation("Dead", new Graphics::Animation(ASSETS_DIR "Swordsman/Dead.png", {0.1f, 0.24f, 0.6f}, true));
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

        if (input.type == sf::Event::MouseButtonPressed || 
            input.type == sf::Event::MouseButtonReleased)
        {
            switch (input.mouseButton.button)
            {
            case sf::Mouse::Left:
                if (input.type == sf::Event::MouseButtonPressed)
                    m_inputFlags |= Attack1;

                else if (input.type == sf::Event::MouseButtonReleased)
                    m_inputFlags &= ~Attack1;

                break;

            case sf::Mouse::Right:
                if (input.type == sf::Event::MouseButtonPressed)
                    m_inputFlags |= Attack2;

                else if (input.type == sf::Event::MouseButtonReleased)
                    m_inputFlags &= ~Attack2;

                break;

            default:
                break;
            }
        }
        else if (input.type == sf::Event::KeyPressed)
        {
            switch (input.key.scancode)
            {
            case sf::Keyboard::W:
                m_inputFlags |= Jump;
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
            case sf::Keyboard::W:
                m_inputFlags &= ~Jump;
                break;

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
        if (isDying() || isAttacking())
            return;

        if (m_health <= 0.f)
        {
            if (m_animator.getCurrent() != "Dead")
                m_animator.setCurrent("Dead");
        
            m_velocity.x = 0.f;
            return;
        }

        // m_health -= 0.5f; for testing purposes of death animation

        const bool attack1 = m_inputFlags & Attack1;
        const bool attack2 = m_inputFlags & Attack2;
        const bool jump = m_inputFlags & Jump;
        const bool left = m_inputFlags & Left;
        const bool right = m_inputFlags & Right;
        const bool run = m_inputFlags & Run;

        if (attack1 || attack2)
        {
            m_animator.setCurrent(attack1 ? "Attack1" : "Attack2");
            m_velocity.x /= ATTACK_SPEED_MULTIPLIER;
            return;
        }

        if (isJumping())
            return;

        if (jump)
        {
            m_velocity.y = -JUMP_SPEED;
            m_animator.setCurrent("Jump");
            m_onGround = false;
        }
        else if (left && !right)
        {
            m_velocity.x = run ? -RUN_SPEED : -WALK_SPEED;
            m_flipped = true;
            m_animator.setCurrent(run ? "Run" : "Walk");
        }
        else if (right && !left)
        {
            m_velocity.x = run ? RUN_SPEED : WALK_SPEED;
            m_flipped = false;
            m_animator.setCurrent(run ? "Run" : "Walk");
        }
        else if (m_onGround)
        {
            m_velocity.x = 0.f;
            m_animator.setCurrent("Idle");
        }
    }

    bool Player::isAttacking() const
    {
        const auto& current = m_animator.getCurrent();
        const auto& currentAnim = m_animator.getCurrentAnimation();

        return (current == "Attack1" || current == "Attack2") &&
               !currentAnim.isFinished();
    }

    bool Player::isJumping() const
    {
        const auto& current = m_animator.getCurrent();

        return (current == "Jump") &&
               !m_onGround;
    }

    bool Player::isDying() const
    {
        const auto& current = m_animator.getCurrent();

        return m_health <= 0.f &&
               current == "Dead";
    }

    bool Player::isDead() const
    {
        const auto& currentAnim = m_animator.getCurrentAnimation();

        return isDying() &&
               currentAnim.isFinished();
    }
}