#pragma once
#include <algorithm>

#include "entityx/System.h"
#include "Shake/Scene/Components/CollisionComponent.h"

namespace Shake
{
    
    class SpawnSystem : public entityx::System<SpawnSystem>
    {
    public:
        SpawnSystem(b2World* physicsWorld)
            : m_physicsWorld(physicsWorld)
        {
            
        }

        void configure(entityx::EventManager& events) override
        {
            
        }

        void update(entityx::EntityManager& em, entityx::EventManager& events, entityx::TimeDelta dt) override
        {
            if (m_initialized)
            {
                return;
            }

            em.each<TransformComponent, CollisionComponent>(
                [this](entityx::Entity entity, TransformComponent& transformComponent, CollisionComponent& collisionComponent)
                {
                    const SVector3 currentPosition = transformComponent.GetPosition();
                    const SVector2 currentScale = transformComponent.GetScale();
                    const float currentRotation = transformComponent.GetRotation();
                    
                    CollisionData& m_collisionData = collisionComponent.m_collisionData;
                    
                    // TODO[rsmekens]: Branching here might be slow
                    b2BodyDef bodyDef;
                    switch (m_collisionData.PhysicsType)
                    {
                    case CollisionType::Static:
                        bodyDef.type = b2_staticBody;
                        break;
                    case CollisionType::Dynamic:
                        bodyDef.type = b2_dynamicBody;
                        break;
                    case CollisionType::Kinematic:
                        bodyDef.type = b2_kinematicBody;
                        break;
                    default:
                        //TODO[rsmekens]: assert here
                        break;
                    }
                    bodyDef.position = b2Vec2(currentPosition.x, currentPosition.y);
                    bodyDef.angle = currentRotation;
                    bodyDef.fixedRotation = m_collisionData.FixedRotation;
                    bodyDef.allowSleep = m_collisionData.AllowSleep;
                    bodyDef.awake = m_collisionData.Awake;
                    
                    // TODO[rsmekens]: should we initialize all the physics body data?
                    collisionComponent.m_physicsBody = m_physicsWorld->CreateBody(&bodyDef);
                    
                    b2PolygonShape collisionShape;
                    collisionShape.SetAsBox(currentScale.x * 0.5f, currentScale.y * 0.5f);
                    
                    b2FixtureDef fixtureDef;
                    fixtureDef.shape = &collisionShape;
                    fixtureDef.density = m_collisionData.Density;
                    fixtureDef.friction = m_collisionData.Friction;
                    
                    collisionComponent.m_physicsBody->CreateFixture(&fixtureDef);
                });

            m_initialized = true;
        }
    private:
        b2World* m_physicsWorld = nullptr;
        bool m_initialized = false;
    };
}
