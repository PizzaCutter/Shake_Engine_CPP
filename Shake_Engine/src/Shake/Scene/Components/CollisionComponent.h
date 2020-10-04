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
    CollisionComponent(const std::vector<std::string>& inData)
    {
        m_collisionData.PhysicsType = static_cast<CollisionType>(SSerialize::DeserializeInt(inData[0]));
        m_collisionData.Density = SSerialize::DeserializeFloat(inData[1]);
        m_collisionData.Friction = SSerialize::DeserializeFloat(inData[2]);

        m_collisionData.FixedRotation = SSerialize::DeserializeInt(inData[3]);
        m_collisionData.AllowSleep = SSerialize::DeserializeInt(inData[4]);
        m_collisionData.Awake = SSerialize::DeserializeInt(inData[5]);
    }
    virtual ~CollisionComponent()
    {
    }


    std::string serialize()
    {
        //std::string serializedData = "[" + "]{";
        std::string serializedData = "";
        serializedData += SSerialize::SerializeInt(static_cast<int>(m_collisionData.PhysicsType));
        serializedData += SSerialize::SerializeFloat(m_collisionData.Density);
        serializedData += SSerialize::SerializeFloat(m_collisionData.Friction);
        
        serializedData += SSerialize::SerializeInt(m_collisionData.FixedRotation);
        serializedData += SSerialize::SerializeInt(m_collisionData.AllowSleep);
        serializedData += SSerialize::SerializeInt(m_collisionData.Awake);
        serializedData += "}";
        return serializedData;
    }

    CollisionData m_collisionData;
    b2Body* m_physicsBody = nullptr;
};
