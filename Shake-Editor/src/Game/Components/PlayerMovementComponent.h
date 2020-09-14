#pragma once
#include "Shake/Core/Input/Input.h"
#include "Shake/Core/Utils/Timestep.h"
#include "Shake/Events/KeyEvent.h"
#include "Shake/Scene/Components/CollisionComponent.h"
#include "Shake/Scene/Entities/ScriptableEntity.h"

namespace Shake
{
    struct PlayerMovementComponent : ScriptableEntity
    {
        PlayerMovementComponent() = default;
        virtual ~PlayerMovementComponent() = default;
        
        float MovementSpeedIncrease{50.0f}; // 0.5f
        float MaxMovementSpeed{10.0f}; // 10.0f
        float VelocityMultiplier {50.0f}; // 0.9f
        float JumpVelocity{5.0f};
        
        CollisionComponent* collisionComponent {nullptr};
        
        void OnCreate() override
        {
            collisionComponent = &GetComponent<CollisionComponent>();
            
        }
        
        void OnDestroy() override
        {
        }
        
        void OnUpdate(Timestep ts) override
        {
            auto currentVelocity = collisionComponent->m_physicsBody->GetLinearVelocity();
            bool ShouldMoveBasedOnInput = false;
            if (Input::IsKeyPressed(KeyCode::D))
            {
                ShouldMoveBasedOnInput = true;
                currentVelocity.x += MovementSpeedIncrease * ts.GetSeconds();
            }
            else if (Input::IsKeyPressed(KeyCode::A))
            {
                currentVelocity.x += -MovementSpeedIncrease * ts.GetSeconds();
                ShouldMoveBasedOnInput = true;
            }

            if(Input::IsKeyDown(KeyCode::Space))
            {
                currentVelocity.y = JumpVelocity;
            }

            currentVelocity.x = SMath::Clamp(currentVelocity.x, -MaxMovementSpeed, MaxMovementSpeed); 

            if(ShouldMoveBasedOnInput == false)
            {
                currentVelocity.x *= VelocityMultiplier * ts.GetSeconds();
            }

            collisionComponent->m_physicsBody->SetLinearVelocity(currentVelocity);
        }
    };
}
