/**
 * @file AnimationComponent.hpp
 * @brief Defines the AnimationComponent class for managing animations.
 */

#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include "ECS/Component.hpp"
#include "Physics/IUpdatable.hpp"
#include "Graphics/Animation.hpp"
#include "Graphics/IRenderable.hpp"

namespace Graphics
{
    /**
     * @class AnimationComponent
     * @brief Represents a component for managing animations.
     *
     * The AnimationComponent class is responsible for managing sprite animations
     * and provides rendering and updating functionality for animated entities.
     */
    class AnimationComponent : 
        public ECS::Component,
        public IRenderable,
        public Physics::IUpdatable
    {
    public:
        /**
         * @brief Constructs an AnimationComponent object.
         *
         * @param entityRef Reference to the entity this component belongs to.
         * @param animationList List of sprite animations associated with the entity.
         * @param currentAnimation The name of the initial animation to set.
         */
        AnimationComponent(ECS::Entity& entityRef,
                           const Animation::List& animationList,
                           const std::string& currentAnimation);

        /**
         * @brief Destructor for cleaning up resources.
         */
        ~AnimationComponent() = default;

        /**
         * @brief Renders the current animation to the screen.
         */
        void render() override;

        /**
         * @brief Updates the animation over time.
         *
         * @param deltaTime The time elapsed since the last update.
         */
        void update(const std::chrono::steady_clock::duration& deltaTime) override;

        /**
         * @brief Sets the current animation to a specified name.
         *
         * @param name The name of the animation to set as the current animation.
         */
        void setAnimation(const std::string& name);

        /**
         * @brief Flips the animation horizontally based on input.
         *
         * @param input A boolean value indicating whether to flip the animation.
         */
        void flip(bool input);

    private:
        bool m_isFlipped {false}; /**< Flag indicating whether the animation is horizontally flipped. */
        std::chrono::steady_clock::duration m_totalTime {0}; /**< Total time elapsed since animation started. */
        std::string m_currentAnimation; /**< Name of the current animation. */
        std::unordered_map<std::string, std::unique_ptr<Animation>> m_animationMap; /**< Map of animation objects. */
    };
}
