#pragma once
#include "Shake/Math/SMath.h"

struct SpriteComponent
{
    SpriteComponent() = default;
    SpriteComponent(const SpriteComponent& spriteComponent) = default;
    SpriteComponent(const SVector4& color)
        : Color(color)
    {
    }


    std::string Name = "SpriteComponent";
    SVector4 Color{1.0f, 1.0f, 1.0f, 1.0f};
};

namespace meta
{
    template <>
    inline auto registerMembers<SpriteComponent>()
    {
        return members(
            member("name", &SpriteComponent::Name),
            member("position", &SpriteComponent::Color)
        );
    }
}
