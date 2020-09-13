#pragma once
#include "Shake/Core/Input/Input.h"
#include "Shake/Core/Utils/Timestep.h"
#include "Shake/Scene/Components/TransformComponent.h"
#include "Shake/Scene/Entities/ScriptableEntity.h"

namespace Shake
{
    class PlayerMovementComponent : public ScriptableEntity
    {
    public:
        float MovementSpeed{10.0f};

        void OnCreate()
        {
        }

        void OnDestroy()
        {
        }

        void OnUpdate(Timestep ts)
        {
            auto& transform = GetComponent<TransformComponent>();

            const float deltaMovement = MovementSpeed * ts.GetSeconds();
            if (Input::IsKeyPressed(KeyCode::D))
            {
                transform.AddPosition(SVector3(1.0f, 0.0f, 0.0f) * deltaMovement);
            }
            else if (Input::IsKeyPressed(KeyCode::A))
            {
                transform.AddPosition(SVector3(-1.0f, 0.0f, 0.0f) * deltaMovement);
            }

            if (Input::IsKeyPressed(KeyCode::W))
            {
                transform.AddPosition(SVector3(0.0f, 1.0f, 0.0f) * deltaMovement);
            }
            else if (Input::IsKeyPressed(KeyCode::S))
            {
                transform.AddPosition(SVector3(0.0f, -1.0f, 0.0f) * deltaMovement);
            }
        }
    };
}
