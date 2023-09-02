/**
 * @file Player.cpp
 * @brief Implements the Player class for representing a game player.
 */

#include "Assets/Player.hpp"
#include "ECS/Component.hpp"
#include "Physics/BodyComponent.hpp"
#include "Inputs/KeyboardController.hpp"
#include "Physics/TransformComponent.hpp"
#include "Graphics/AnimationComponent.hpp"

using namespace Assets;

/**
 * @brief Constructs a Player object and initializes its components.
 *
 * The constructor initializes a Player object by adding various components to it,
 * including a KeyboardController for input handling, a BodyComponent for physics simulation,
 * a TransformComponent for managing the player's position, and an AnimationComponent for animations.
 */
Player::Player()
{
    // Add a KeyboardController component for input handling.
    this->addComponent<Inputs::KeyboardController>();

    // Add a BodyComponent with a specified mass for physics simulation.
    this->addComponent<Physics::BodyComponent>(50.0f);

    // Add a TransformComponent with initial X and Y coordinates for position management.
    this->addComponent<Physics::TransformComponent>(100.0f, 100.0f);

    // Add an AnimationComponent with animations specified in a list and set the current animation.
    this->addComponent<Graphics::AnimationComponent>(
        Graphics::Animation::List{
            {"Idle", new Graphics::Animation(ASSETS_DIR "Archer/Idle.png", 6)},
            {"Walk", new Graphics::Animation(ASSETS_DIR "Archer/Walk.png", 8)}
        },
        "Idle"
    );
}
