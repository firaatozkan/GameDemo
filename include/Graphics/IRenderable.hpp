#pragma once

namespace Graphics
{
    class IRenderable
    {
    public:
        virtual ~IRenderable() = default;
        virtual void render() = 0;
    };
}