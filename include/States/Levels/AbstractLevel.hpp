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
    template <typename T>
    class AbstractLevel : public AbstractState
    {
    private:
        void registerComponents();

    protected:

        template <typename U, typename = std::enable_if_t<std::is_base_of_v<ECS::Entity, U>>>
        U& addEntity()
        {
            return *(reinterpret_cast<U*>(m_entityVector.emplace_back(std::make_unique<U>()).get()));
        }

    public:
        AbstractLevel();
        virtual ~AbstractLevel() = default;
        void handleInput(const SDL_Event& event) override;
        void updateState(const std::chrono::steady_clock::duration& deltaTime) override;
        void renderState() override;

    private:
        std::vector<std::unique_ptr<ECS::Entity>> m_entityVector;
        std::vector<std::reference_wrapper<Inputs::IInputable>> m_inputableVector;
        std::vector<std::reference_wrapper<Physics::IUpdatable>> m_updatableVector;
        std::vector<std::reference_wrapper<Graphics::IRenderable>> m_renderableVector;
    };
}

template <typename T>
States::Levels::AbstractLevel<T>::AbstractLevel()
{
    static_cast<T*>(this)->initializeLevel();
    this->registerComponents();
}

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

template <typename T>
void States::Levels::AbstractLevel<T>::handleInput(const SDL_Event& event)
{
    if (event.type == SDL_QUIT)
        exit(EXIT_SUCCESS);

    for (Inputs::IInputable& inputable : m_inputableVector)
        inputable.handleInput(event);
}

template <typename T>
void States::Levels::AbstractLevel<T>::updateState(const std::chrono::steady_clock::duration& deltaTime)
{
    for (Physics::IUpdatable& updatable : m_updatableVector)
        updatable.update(deltaTime);
}

template <typename T>
void States::Levels::AbstractLevel<T>::renderState()
{
    SDL_SetRenderDrawColor(Core::GameWindow::get().getRenderer(), T::color_red, T::color_green, T::color_blue, T::color_alpha);
    SDL_RenderClear(Core::GameWindow::get().getRenderer());

    for (Graphics::IRenderable& renderable : m_renderableVector)
        renderable.render();

    SDL_RenderPresent(Core::GameWindow::get().getRenderer());
}