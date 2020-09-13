#pragma once
#include "Shake/Core/Input/Input.h"
#include "Shake/Core/Utils/Timestep.h"
#include "Shake/Scene/Components/CollisionComponent.h"
#include "Shake/Scene/Components/TransformComponent.h"
#include "Shake/Scene/Entities/ScriptableEntity.h"

namespace Shake
{
    struct PlayerMovementComponent : ScriptableEntity
    {
        PlayerMovementComponent() = default;
        virtual ~PlayerMovementComponent() = default;
        
        float MovementSpeed{10.0f};

        void OnCreate() override
        {
        }
        
        void OnDestroy() override
        {
        }
        
        void OnUpdate(Timestep ts) override
        {
            auto& collisionComponent = GetComponent<CollisionComponent>();
            const auto currentVelocity = collisionComponent.m_physicsBody->GetLinearVelocity();
            if (Input::IsKeyPressed(KeyCode::D))
            {
                collisionComponent.m_physicsBody->SetLinearVelocity(b2Vec2(MovementSpeed, currentVelocity.y));
            }
            else if (Input::IsKeyPressed(KeyCode::A))
            {
                collisionComponent.m_physicsBody->SetLinearVelocity(b2Vec2(-MovementSpeed, currentVelocity.y));
            }
        }
    };
}
