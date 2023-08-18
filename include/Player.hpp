#pragma once

struct Vec2D;
class Animation;

class Player : public IRenderable, public IUpdatable
{
public:
    enum PlayerStates
    {
        IDLE,
        WALK,
        JUMP,
        
        NUM_OF_PLAYER_STATES
    };

    Player(SDL_Renderer& rendererRef);
    ~Player();
    void handleInput(const SDL_Event& event);
    void render() override;
    void update(unsigned int deltaTime) override;

private:
    bool m_isFacingRight {true};
    PlayerStates m_currentState {IDLE};
    long long m_lastDuration {0};
    Animation* m_animationArray[NUM_OF_PLAYER_STATES];

    Vec2D m_forceVector;
    Vec2D m_frictionVector;
    
    Vec2D m_accelerationVec;
    Vec2D m_velocityVec;
    Vec2D m_positionVec;
};