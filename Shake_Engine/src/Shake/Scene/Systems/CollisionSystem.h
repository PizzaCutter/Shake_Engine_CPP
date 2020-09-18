#pragma once
#include <algorithm>

#include "entityx/System.h"
#include "Shake/Scene/Components/CollisionComponent.h"
#include "Shake/Scene/Components/TransformComponent.h"

namespace Shake
{
    
    class CollisionSystem : public entityx::System<CollisionSystem>
    {
    public:
        CollisionSystem()
        {
            
        }

        void configure(entityx::EventManager& events) override
        {
            
        }

        void update(entityx::EntityManager& em, entityx::EventManager& events, entityx::TimeDelta dt) override
        {
            em.each<TransformComponent, CollisionComponent>(
                [this](entityx::Entity entity, TransformComponent& transformComponent,
                       CollisionComponent& collisionComponent)
                {
                    const auto position = collisionComponent.m_physicsBody->GetPosition();
                    const auto rotation = collisionComponent.m_physicsBody->GetAngle();
                    transformComponent.SetPositionAndRotation(SVector3(position.x, position.y, 0.0f), rotation);
                    transformComponent.SetPositionAndRotation(SVector3(position.x, position.y, 0.0f), rotation);
                });
        }
    };
}
