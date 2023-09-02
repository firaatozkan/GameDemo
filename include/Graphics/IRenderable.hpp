/**
 * @file IRenderable.hpp
 * @brief Defines the IRenderable interface for renderable objects.
 */

#pragma once

namespace Graphics
{
    /**
     * @class IRenderable
     * @brief An interface for objects that can be rendered.
     *
     * The IRenderable interface defines a contract for objects that can be rendered
     * to a graphics context. Classes implementing this interface should provide
     * the ability to render themselves when required.
     */
    class IRenderable
    {
    public:
        /**
         * @brief Virtual destructor for proper cleanup in derived classes.
         */
        virtual ~IRenderable() = default;

        /**
         * @brief Renders the object to a graphics context.
         */
        virtual void render() = 0;
    };
}
