#pragma once

#include "box2d/box2d.h"
#include "Shake/Serialization/metastuff/example/nlohmann_json/json.hpp"

enum CollisionType
{
    Static = 0,
    Dynamic = 1,
    Kinematic = 2
};

struct CollisionData
{
    int PhysicsType = static_cast<int>(CollisionType::Static);

    float Density = 1.0f;
    float Friction = 0.5f;

    bool FixedRotation = false;
    bool AllowSleep = false;
    bool Awake = true;
};

namespace meta
{
    template <>
    inline auto registerMembers<CollisionData>()
    {
        return members(
            member("physicsType", &CollisionData::PhysicsType),
            member("density", &CollisionData::Density),
            member("friction", &CollisionData::Friction),
            member("fixedRotation", &CollisionData::FixedRotation),
            member("allowSleep", &CollisionData::AllowSleep),
            member("awake", &CollisionData::Awake) 
        );
    }
}

struct CollisionComponent
{
    CollisionComponent() = default;
    CollisionComponent(const CollisionData& data)
        : CollisionData(data)
    {
    }
    CollisionComponent(const std::vector<std::string>& inData)
    {
        CollisionData.PhysicsType = static_cast<CollisionType>(SSerialize::DeserializeInt(inData[0]));
        CollisionData.Density = SSerialize::DeserializeFloat(inData[1]);
        CollisionData.Friction = SSerialize::DeserializeFloat(inData[2]);

        CollisionData.FixedRotation = SSerialize::DeserializeInt(inData[3]);
        CollisionData.AllowSleep = SSerialize::DeserializeInt(inData[4]);
        CollisionData.Awake = SSerialize::DeserializeInt(inData[5]);
    }
    virtual ~CollisionComponent()
    {
    }

    std::string Name = "CollisionComponent";
    CollisionData CollisionData;
    b2Body* m_physicsBody = nullptr;
};

namespace meta
{
    template <>
    inline auto registerMembers<CollisionComponent>()
    {
        return members(
            member("name", &CollisionComponent::Name),
            member("collision_data", &CollisionComponent::CollisionData)
        );
    }
}
