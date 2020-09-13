#pragma once

#include "Components.h"
#include "TransformComponent.h"
#include "box2d/box2d.h"
#include "Shake/Scene/Entities/ScriptableEntity.h"

enum class CollisionType
{
    Static = 0,
    Dynamic = 1,
    Kinematic = 2
};

struct CollisionData
{
    CollisionType PhysicsType = CollisionType::Static;

    float Density = 1.0f;
    float Friction = 0.5f;

    bool FixedRotation = false;
    bool AllowSleep = false;
    bool Awake = true;
};

struct BaseComponent
{
    int handleThing = 0;
    
    virtual ~BaseComponent() = default; 

    virtual void OnCreate(Shake::Entity entity) 
    {
        
    }
};

struct CollisionComponent
{
public:
    
    CollisionComponent() = default;
    CollisionComponent(const CollisionComponent& other) = default;

    CollisionComponent(const CollisionData& data)
        : m_collisionData(data) 
    {
    }

    void OnCreate(Shake::Entity entity) 
    {
        auto& m_transformComponent(entity.GetComponent<Shake::TransformComponent>());
        const SVector3 currentPosition = m_transformComponent.GetPosition();
        
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
        bodyDef.angle = m_transformComponent.GetRotation();
        bodyDef.fixedRotation = m_collisionData.FixedRotation;
        bodyDef.allowSleep = m_collisionData.AllowSleep;
        bodyDef.awake = m_collisionData.Awake;
        // TODO[rsmekens]: should we initialize all the physics body data?
        
        m_physicsBody = entity.m_scene->m_physicsWorld->CreateBody(&bodyDef);
        
        b2PolygonShape collisionShape;
        collisionShape.SetAsBox(0.5f, 0.5f);
        
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &collisionShape;
        fixtureDef.density = m_collisionData.Density;
        fixtureDef.friction = m_collisionData.Friction;
        
        m_physicsBody->CreateFixture(&fixtureDef);
    }
    
    // TODO[rsmekens]: Don't really like that we have to cache data here :/ 
    CollisionData m_collisionData;
    b2Body* m_physicsBody = nullptr;
};
