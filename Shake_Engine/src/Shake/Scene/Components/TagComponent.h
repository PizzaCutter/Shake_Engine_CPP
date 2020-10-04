#pragma once
#include "Shake/Math/SMath.h"
#include <string>

#include "Shake/Serialization/SSerialize.h"

struct TagComponent
{
    std::string Name = "TagComponent";
    std::string ObjectName;
    uint32_t ComponentId;

    TagComponent() = default;
    TagComponent(const TagComponent&) = default;
    TagComponent(const std::string& objectName, uint32_t id)
        : ObjectName(objectName), ComponentId(id)
    {
    }

    TagComponent(const std::vector<std::string>& inData)
    {
        ObjectName = inData[0];
        ComponentId = SSerialize::DeserializeInt(inData[1]);
    }
};

namespace meta
{
    template <>
    inline auto registerMembers<TagComponent>()
    {
        return members(
            member("name", &TagComponent::Name),
            member("object_name", &TagComponent::ObjectName),
            member("component_id", &TagComponent::ComponentId)
        );
    }
} 
