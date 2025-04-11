#include <cassert>
#include <iostream>
#include "Animation.hpp"
#include "GameWindow.hpp"

Animation::Animation(std::string_view filePath,
                     unsigned int frameCount,
                     float frameTime,
                     bool oneShot)
    : m_oneShot(oneShot)
{
    initSprite(filePath);

    const auto& textureRect = m_sprite.getTextureRect();

    for (unsigned int i = 0; i < frameCount; ++i)
        m_frameVector.emplace_back(sf::IntRect((textureRect.width / frameCount) * i,
                                               textureRect.top,
                                               textureRect.width / frameCount,
                                               textureRect.height),
                                   frameTime);

    m_sprite.setTextureRect(m_frameVector.front().first);
}

Animation::Animation(std::string_view filePath,
                     std::initializer_list<float> frameTimes,
                     bool oneShot)
    : m_oneShot(oneShot)
{
    initSprite(filePath);

    const auto &textureRect = m_sprite.getTextureRect();

    unsigned int i = 0;

    for (auto&& frameTime : frameTimes)
    {
        m_frameVector.emplace_back(sf::IntRect((textureRect.width / static_cast<int>(frameTimes.size())) * i++,
                                               textureRect.top,
                                               textureRect.width / static_cast<int>(frameTimes.size()),
                                               textureRect.height),
                                   frameTime);
    }

    m_sprite.setTextureRect(m_frameVector.front().first);
}

void Animation::initSprite(std::string_view filePath)
{
    const bool loaded = m_texture.loadFromFile(filePath.data());
    assert(loaded);
    m_sprite.setTexture(m_texture);
}

void Animation::update(float deltaTime)
{
    m_currentTime += deltaTime;

    if (m_currentTime >= m_frameVector[m_frameIndex].second)
    {
        m_sprite.setTextureRect(m_frameVector[m_frameIndex++].first);
        m_currentTime = 0.0f;

        if (m_frameIndex >= m_frameVector.size())
        {
            if (!m_oneShot)
                m_frameIndex = 0;
            else
            {
                m_finished = true;
                m_frameIndex = m_frameVector.size() - 1;
            }
        }
    }
}

sf::FloatRect Animation::getBounds() const
{
    return m_sprite.getGlobalBounds();
}

void Animation::draw(const sf::Vector2f& position, bool isFlipped)
{
    if (isFlipped)
    {
        m_sprite.setScale(-1.f, 1.f);
        m_sprite.setOrigin(m_sprite.getLocalBounds().width, 0.f);
    }
    else
    {
        m_sprite.setScale(1.f, 1.f);
        m_sprite.setOrigin(0.f, 0.f);
    }

    m_sprite.setPosition(position);

    GameWindow::get().getWindow().draw(m_sprite);
}

void Animation::resetAnimation()
{
    m_frameIndex = 0;
    m_finished = false;
}

bool Animation::isFinished() const
{
    return m_finished;
}
