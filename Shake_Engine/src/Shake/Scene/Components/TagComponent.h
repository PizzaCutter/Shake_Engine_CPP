#pragma once
#include "Shake/Math/SMath.h"
#include <string>

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

        TagComponent(const std::string& inData)
        {
            uint32_t temp = 0;
            const uint32_t objectNameStartIndex = inData.substr(temp).find_first_of("{") + temp + 1;
            temp = objectNameStartIndex;
            const uint32_t objectNameEndIndex = inData.substr(objectNameStartIndex + 1).find_first_of("}") + temp + 1;

            temp = objectNameEndIndex;
            const uint32_t idStartIndex = inData.substr(temp).find_first_of("{") + temp + 1;
            temp = idStartIndex;
            const uint32_t idEndIndex = inData.substr(idStartIndex + 1).find_first_of("}") + temp + 1;

            ObjectName = inData.substr(objectNameStartIndex,
                                                         objectNameEndIndex - objectNameStartIndex);
            const std::string idAsString = inData.substr(idStartIndex, idEndIndex - idStartIndex);
            ComponentId = std::stoi(idAsString);
        }

        static std::string GetComponentName()
        {
            return "TagComponent";
        }

        std::string serialize()
        {
            std::string outString;
            outString += "[" + GetComponentName() + "]{";
            outString += "{" + ObjectName + "}";
            outString += "{" + std::to_string(ComponentId) + "}}";
            return outString;
        }
    };
}    