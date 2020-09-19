#pragma once

#include "../../../../../Shake-Editor/src/Game/Components/PlayerMovementComponent.h"
#include "entityx/System.h"
#include "Shake/Core/Input/Input.h"

namespace Shake
{
    class PlayerMovementSystem : public entityx::System<PlayerMovementSystem>
    {
    public:
        PlayerMovementSystem()
        {
        }

        void configure(entityx::EventManager& events) override
        {
        }

        void update(entityx::EntityManager& em, entityx::EventManager& events, entityx::TimeDelta dt) override
        {
            em.each<PlayerMovementComponent, CollisionComponent>(
                [this, dt](entityx::Entity entity, PlayerMovementComponent& playerMovementComponent, CollisionComponent& collisionComponent)
                {
                    auto currentVelocity = collisionComponent.m_physicsBody->GetLinearVelocity();
                    bool ShouldMoveBasedOnInput = false;
                    if (Input::IsKeyPressed(KeyCode::D))
                    {
                        ShouldMoveBasedOnInput = true;
                        currentVelocity.x += playerMovementComponent.MovementSpeedIncrease * dt;
                    }
                    else if (Input::IsKeyPressed(KeyCode::A))
                    {
                        currentVelocity.x += -playerMovementComponent.MovementSpeedIncrease * dt;
                        ShouldMoveBasedOnInput = true;
                    }

                    if (Input::IsKeyDown(KeyCode::Space))
                    {
                        currentVelocity.y = playerMovementComponent.JumpVelocity;
                    }

                    currentVelocity.x = SMath::Clamp(currentVelocity.x, -playerMovementComponent.MaxMovementSpeed,
                                                     playerMovementComponent.MaxMovementSpeed);

                    if (ShouldMoveBasedOnInput == false)
                    {
                        currentVelocity.x *= playerMovementComponent.VelocityMultiplier * dt;
                    }

                    collisionComponent.m_physicsBody->SetLinearVelocity(currentVelocity);
                });
        }
    };
}
