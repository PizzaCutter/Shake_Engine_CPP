#pragma once
#include "Shake/Math/SMath.h"

namespace Shake
{
    struct TransformComponent 
    {
    public:
        SMat4 Transform {SMat4(1.0f)};

        TransformComponent() = default;
        TransformComponent(const TransformComponent&) = default;
        TransformComponent(const SMat4& transform) : Transform(transform) {};

        operator SMat4&() { return Transform; }
        operator const SMat4&() const { return Transform; }
    };

    struct SpriteComponent
    {
    public:
        SVector4 Color{1.0f, 1.0f, 1.0f, 1.0f};

        SpriteComponent() = default;
        SpriteComponent(const SpriteComponent&) = default;
        SpriteComponent(const SVector4& color) : Color(color) {}
    };
}
