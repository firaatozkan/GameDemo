#pragma once

#include <SFML/Graphics.hpp>

class Animation
{
public:
    Animation(std::string_view filePath, unsigned int frameCount, float frameTime, bool oneShot = false);
    Animation(std::string_view filePath, std::initializer_list<float> frameTimes, bool oneShot = false);

    ~Animation() = default;

    sf::FloatRect getBounds() const;
    
    void update(float deltaTime);

    void draw(const sf::Vector2f& position, bool isFlipped);

    void resetAnimation();

    bool isFinished() const;

private:
    void initSprite(std::string_view filePath);
    
    sf::Sprite m_sprite;
    sf::Texture m_texture;

    const bool m_oneShot;
    float m_currentTime = 0.0f;
    size_t m_frameIndex = 0;
    bool m_finished {false};
    std::vector<std::pair<sf::IntRect, float>> m_frameVector;
};