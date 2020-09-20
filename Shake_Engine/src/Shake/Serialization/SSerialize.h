#pragma once

#include <string>

#include "Shake/Math/SMath.h"


class SSerialize
{
public:
    static std::string Serialize(const SVector3& inVec)
    {
        return "{" + std::to_string(inVec.x) + "," + std::to_string(inVec.y) + "," + std::to_string(inVec.z) + "}";
    }
    static SVector3 Deserialize(const std::string& inData)
    {
        return SVector3();
        // PARSE X LOCATION 
        const uint32_t positionXStartIndex = inData.find_first_of("{");
        const uint32_t positionXEndIndex = inData.find_first_of(",");

        // PARSE Y LOCATION
        uint32_t temp = positionXEndIndex;
        const uint32_t positionYStartIndex = inData.substr(temp).find_first_of(",") + temp + 1;
        temp = positionYStartIndex;
        const uint32_t positionYEndIndex = inData.substr(temp).find_first_of(",") + temp;

        // PARSE Z LOCATION
        temp = positionYEndIndex;
        const uint32_t positionZStartIndex = inData.substr(temp).find_first_of(",") + temp + 1;
        temp = positionZStartIndex;
        const uint32_t positionZEndIndex = inData.substr(temp).find_first_of("}") + temp;

        const std::string positionXAsString = inData.substr(positionXStartIndex, positionXEndIndex - positionXStartIndex);
        const std::string positionYAsString = inData.substr(positionYStartIndex, positionYEndIndex - positionYStartIndex);
        const std::string positionZAsString = inData.substr(positionZStartIndex, positionZEndIndex - positionZStartIndex);
        
        std::string::size_type sz;
        return SVector3(
                std::stof(positionXAsString, &sz), std::stof(positionYAsString, &sz), std::stof(positionZAsString, &sz)
            ); 
    }
    
};
