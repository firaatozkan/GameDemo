#pragma once

struct Vec2D;
class Animation;

class Player : public IRenderable, public IUpdatable, public RigidBody
{
public:
    enum PlayerStates
    {
        IDLE,
        WALK,
        JUMP,
        RUN,
        
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
};