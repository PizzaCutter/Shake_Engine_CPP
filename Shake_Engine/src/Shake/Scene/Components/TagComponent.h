#pragma once
#include "Shake/Math/SMath.h"
#include <string>

#include "Shake/Serialization/SSerialize.h"

namespace Shake
{
    struct TagComponent 
    {
        std::string ObjectName; 
        uint32_t ComponentId;

        TagComponent(const std::string& objectName, uint32_t id)
            : ObjectName(objectName), ComponentId(id)
        {
        }

        TagComponent(const std::vector<std::string>& inData)
        {
            ObjectName = inData[0];
            ComponentId = SSerialize::DeserializeInt(inData[1]);
        }

        static std::string GetComponentName()
        {
            return "TagComponent";
        }

        std::string serialize()
        {
            std::string outString;
            outString += "[" + GetComponentName() + "]{";
            outString += SSerialize::SerializeString(ObjectName);
            outString += SSerialize::SerializeInt(ComponentId);
            return outString;
        }
    };
}    