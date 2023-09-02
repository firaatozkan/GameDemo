#include "Assets/Player.hpp"
#include "ECS/Component.hpp"
#include "Physics/BodyComponent.hpp"
#include "Inputs/KeyboardController.hpp"
#include "Physics/TransformComponent.hpp"
#include "Graphics/AnimationComponent.hpp"

using namespace Assets;

Player::Player()
{
    this->addComponent<Inputs::KeyboardController>();
    this->addComponent<Physics::BodyComponent>(50.0f);
    this->addComponent<Physics::TransformComponent>(100.0f, 100.0f);
    this->addComponent<Graphics::AnimationComponent>(Graphics::Animation::List{{"Idle", new Graphics::Animation(ASSETS_DIR "Archer/Idle.png", 6)},
                                                                               {"Walk", new Graphics::Animation(ASSETS_DIR "Archer/Walk.png", 8)}},
                                                     "Idle");
}