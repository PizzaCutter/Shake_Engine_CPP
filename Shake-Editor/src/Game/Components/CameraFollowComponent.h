#pragma once
#include <algorithm>
#include <entt.hpp>

//
// #include "PlayerMovementComponent.h"
// #include "Shake/Core/Utils/Timestep.h"
// #include "Shake/Scene/Components/Components.h"
// #include "Shake/Scene/Components/TransformComponent.h"
// #include "Shake/Scene/Entities/ScriptableEntity.h"
//
// struct CameraFollowComponent : Shake::ScriptableEntity
// {
// public:
//    CameraFollowComponent() = default;
//    CameraFollowComponent(const CameraFollowComponent& other) = default;
//    virtual ~CameraFollowComponent() = default;
//
//    Shake::TransformComponent* ownTransformComponent {nullptr};
//    Shake::TransformComponent* transformComponentToFollow { nullptr };
//    
//    void OnCreate() override
//    {
//       ownTransformComponent = &GetComponent<Shake::TransformComponent>();
//
//       auto view = m_entity.m_scene->m_registry.view<Shake::NativeScriptComponent>();
//       for (auto entity : view)
//       {
//          Shake::Entity tempEntity {entity, m_entity.m_scene};
//          auto& transformComponent = tempEntity.GetComponent<Shake::TransformComponent>();
//          auto& nativeScriptComponent = tempEntity.GetComponent<Shake::NativeScriptComponent>();
//          auto cameraFollowComponent = static_cast<CameraFollowComponent*>(nativeScriptComponent.Instance); 
//          if(cameraFollowComponent != nullptr)
//          {
//             continue;
//          }
//
//          transformComponentToFollow = &transformComponent;
//       }
//    }
//    
//    void OnDestroy() override
//    {
//       
//    }
//    
//    void OnUpdate(Shake::Timestep ts) override
//    {
//       SVector3 newPlayerPosition = transformComponentToFollow->GetPosition();
//       SVector3 newCameraPosition = SVector3(-newPlayerPosition.x, -newPlayerPosition.y, ownTransformComponent->GetPosition().z);
//       ownTransformComponent->SetPosition(newCameraPosition);
//    }
// };
