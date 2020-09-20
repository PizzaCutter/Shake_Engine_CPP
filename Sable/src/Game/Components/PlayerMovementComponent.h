#pragma once

namespace Shake
{
    struct PlayerMovementComponent
    {
        float MovementSpeedIncrease{50.0f}; // 0.5f
        float MaxMovementSpeed{10.0f}; // 10.0f
        float VelocityMultiplier {50.0f}; // 0.9f
        float JumpVelocity{5.0f};
    };
}
