#pragma once

#include "box2d/box2d.h"

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

struct CollisionComponent
{
    CollisionComponent(const CollisionData& data)
        : m_collisionData(data) 
    {
    }
    
    CollisionData m_collisionData;
    b2Body* m_physicsBody = nullptr;
};
