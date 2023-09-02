/**
 * @file AbstractLevel.hpp
 * @brief Defines the AbstractLevel class for game levels.
 */

#pragma once

#include <vector>
#include <SDL2/SDL.h>
#include "ECS/Entity.hpp"
#include "ECS/Component.hpp"
#include "Core/GameWindow.hpp"
#include "Inputs/IInputable.hpp"
#include "Physics/IUpdatable.hpp"
#include "States/AbstractState.hpp"
#include "Graphics/IRenderable.hpp"

namespace States::Levels
{
    /**
     * @brief An abstract class representing a game level.
     *
     * This class serves as a base for creating different game levels.
     *
     * @tparam T The derived level class.
     */
    template <typename T>
    class AbstractLevel : public AbstractState
    {
    private:
        /**
         * @brief Register components for this level.
         *
         * This method populates vectors with components for the entities in the level.
         */
        void registerComponents();

    protected:
        /**
         * @brief Add an entity to the level.
         *
         * This method creates and adds a new entity to the level.
         *
         * @tparam U The type of the entity to add.
         * @return A reference to the added entity.
         */
        template <typename U, typename = std::enable_if_t<std::is_base_of_v<ECS::Entity, U>>>
        U& addEntity();

    public:
        /**
         * @brief Constructs an AbstractLevel object.
         */
        AbstractLevel();

        /**
         * @brief Destroys the AbstractLevel object.
         */
        virtual ~AbstractLevel() = default;

        /**
         * @brief Handle input events for the level.
         *
         * This method handles input events, such as keyboard and mouse events, for the level.
         *
         * @param event The SDL event to handle.
         */
        void handleInput(const SDL_Event& event) override;

        /**
         * @brief Update the state of the level.
         *
         * This method updates the state of the level based on the elapsed time.
         *
         * @param deltaTime The time since the last update.
         */
        void updateState(const std::chrono::steady_clock::duration& deltaTime) override;

        /**
         * @brief Render the state of the level.
         *
         * This method renders the current state of the level.
         */
        void renderState() override;

    private:
        std::vector<std::unique_ptr<ECS::Entity>> m_entityVector; /** A vector of entities in the level. */
        std::vector<std::reference_wrapper<Inputs::IInputable>> m_inputableVector; /** A vector of inputable component references. */
        std::vector<std::reference_wrapper<Physics::IUpdatable>> m_updatableVector; /** A vector of updatable component references. */
        std::vector<std::reference_wrapper<Graphics::IRenderable>> m_renderableVector; /** A vector of renderable component references. */
    };
}

/**
 * @brief Constructs an AbstractLevel object.
 */
template <typename T>
States::Levels::AbstractLevel<T>::AbstractLevel()
{
    static_cast<T*>(this)->initializeLevel();
    this->registerComponents();
}

/**
 * @brief Register components for this level.
 *
 * This method populates vectors with components for the entities in the level.
 */
template <typename T>
void States::Levels::AbstractLevel<T>::registerComponents()
{
    for (const auto& entity : m_entityVector)
    {
        for (const auto& [_, component] : entity->getComponentMap())
        {
            auto inputable = dynamic_cast<Inputs::IInputable*>(component.get());
            if (inputable)
                m_inputableVector.emplace_back(*inputable);
                
            auto updatable = dynamic_cast<Physics::IUpdatable*>(component.get());
            if (updatable)
                m_updatableVector.emplace_back(*updatable);

            auto renderable = dynamic_cast<Graphics::IRenderable*>(component.get());
            if (renderable)
                m_renderableVector.emplace_back(*renderable);
        }
    }
}

/**
 * @brief Add an entity to the level.
 *
 * This method creates and adds a new entity to the level.
 *
 * @tparam U The type of the entity to add.
 * @return A reference to the added entity.
 */
template <typename T>
template <typename U, typename>
U& States::Levels::AbstractLevel<T>::addEntity()
{
    return *(reinterpret_cast<U*>(m_entityVector.emplace_back(std::make_unique<U>()).get()));
}

/**
 * @brief Handle input events for the level.
 *
 * This method handles input events, such as keyboard and mouse events, for the level.
 *
 * @param event The SDL event to handle.
 */
template <typename T>
void States::Levels::AbstractLevel<T>::handleInput(const SDL_Event& event)
{
    if (event.type == SDL_QUIT)
        exit(EXIT_SUCCESS);

    for (Inputs::IInputable& inputable : m_inputableVector)
        inputable.handleInput(event);
}

/**
 * @brief Update the state of the level.
 *
 * This method updates the state of the level based on the elapsed time.
 *
 * @param deltaTime The time since the last update.
 */
template <typename T>
void States::Levels::AbstractLevel<T>::updateState(const std::chrono::steady_clock::duration& deltaTime)
{
    for (Physics::IUpdatable& updatable : m_updatableVector)
        updatable.update(deltaTime);
}

/**
 * @brief Render the state of the level.
 *
 * This method renders the current state of the level.
 */
template <typename T>
void States::Levels::AbstractLevel<T>::renderState()
{
    SDL_SetRenderDrawColor(Core::GameWindow::get().getRenderer(), T::color_red, T::color_green, T::color_blue, T::color_alpha);
    SDL_RenderClear(Core::GameWindow::get().getRenderer());

    for (Graphics::IRenderable& renderable : m_renderableVector)
        renderable.render();

    SDL_RenderPresent(Core::GameWindow::get().getRenderer());
}
