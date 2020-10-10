#pragma once

#include "Shake/Serialization/metastuff/example/nlohmann_json/json.hpp""
#include "Shake/Serialization/metastuff/include/Meta.h"

struct PlayerMovementComponent
{
    std::string Name = "PlayerMovementComponent";
    float MovementSpeedIncrease{50.0f}; // 0.5f
    float MaxMovementSpeed{10.0f}; // 10.0f
    float VelocityMultiplier{50.0f}; // 0.9f
    float JumpVelocity{5.0f};
};

namespace meta
{
    template <>
    inline auto registerMembers<PlayerMovementComponent>()
    {
        return members(
            member("name", &PlayerMovementComponent::Name),
            member("movementSpeedIncrease", &PlayerMovementComponent::MovementSpeedIncrease),
            member("maxMovementSpeed", &PlayerMovementComponent::MaxMovementSpeed),
            member("velocityMultiplier", &PlayerMovementComponent::VelocityMultiplier),
            member("jumpVelocity", &PlayerMovementComponent::JumpVelocity)
        );
    }
}