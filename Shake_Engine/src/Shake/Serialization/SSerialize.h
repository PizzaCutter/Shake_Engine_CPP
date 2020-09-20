#pragma once

#include <string>

#include "Shake/Math/SMath.h"

namespace SSerialize
{
    static std::string SerializeFloat(const float& other)
    {
        return "{" + std::to_string(other) + "}";
    }

    static float DeserializeFloat(const std::string& other)
    {
        return std::stof(other);
    }

    static std::string SerializeInt(const int& other)
    {
        return "{" + std::to_string(other) + "}";
    }

    static int DeserializeInt(const std::string& other)
    {
       return std::stoi(other); 
    }

    static std::string SerializeString(const std::string& other)
    {
        return "{" + other + "}";
    }
}
