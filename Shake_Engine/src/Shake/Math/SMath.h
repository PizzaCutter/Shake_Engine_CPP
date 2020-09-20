#pragma once

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include <string>

#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale

#include <algorithm>

//#define SVector2 glm::vec2
//#define SVector3 glm::vec3
#define SVector4 glm::vec4

#define SMat3 glm::mat3
#define SMat4 glm::mat4

struct SVector3 : glm::vec3
{
    SVector3(const float& x, const float& y, const float& z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    SVector3(const float& scalar)
    {
        this->x = scalar;
        this->y = scalar;
        this->z = scalar;
    }

    SVector3()
        : SVector3(0.0f)
    {
        
    }

    operator glm::vec3() const { return *this; }
    
    SVector3& operator=(const glm::vec3& other) 
    {
        this->x = other.x;
        this->y = other.y;
        this->z = other.z;
        return *this;
    }
    SVector3& operator+(const glm::vec3& other)
    {
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;
        return *this; 
    }

    
    std::string Serialize() const
    {
        return "{" + std::to_string(this->x) + "," + std::to_string(this->y) + "," + std::to_string(this->z) + "}";
    }
    
    static SVector3 Deserialize(const std::string& inData)
    {
        // PARSE X LOCATION 
        const uint32_t positionXEndIndex = inData.find_first_of(",");
        const uint32_t positionYEndIndex= inData.substr(positionXEndIndex + 1).find_first_of(",");
    
        const std::string positionXAsString = inData.substr(0, positionXEndIndex);
        const std::string positionYAsString = inData.substr(positionXEndIndex + 1, positionYEndIndex);
        const std::string positionZAsString = inData.substr( positionXEndIndex + positionYEndIndex + 2);
        
        std::string::size_type sz;
        return SVector3(
                std::stof(positionXAsString, &sz), std::stof(positionYAsString, &sz), std::stof(positionZAsString, &sz)
            ); 
    }
};

struct SVector2 : glm::vec2
{
    SVector2(const float& x, const float& y)
    {
        this->x = x;
        this->y = y;
    }

    SVector2(const float& scalar)
    {
        this->x = scalar;
        this->y = scalar;
    }

    SVector2()
        : SVector2(0.0f)
    {
        
    }

    operator glm::vec2() const { return *this; }
    
    SVector2& operator=(const glm::vec2& other) 
    {
        this->x = other.x;
        this->y = other.y;
        return *this;
    }
    SVector2& operator+(const glm::vec2& other)
    {
        this->x += other.x;
        this->y += other.y;
        return *this; 
    }
    const SVector2& operator*(const SVector2& other) const
    {
        return *this * other;
    }
    const SVector2& operator*(const float& other) const
    {
        return *this * other;
    }
    
    std::string Serialize() const
    {
        return "{" + std::to_string(this->x) + "," + std::to_string(this->y) + "}";
    }
    
    static SVector2 Deserialize(const std::string& inData)
    {
        // PARSE X LOCATION 
        const uint32_t positionXEndIndex = inData.find_first_of(",");
        const uint32_t positionYEndIndex= inData.substr(positionXEndIndex + 1).find_first_of(",");
    
        const std::string positionXAsString = inData.substr(0, positionXEndIndex);
        const std::string positionYAsString = inData.substr(positionXEndIndex + 1, positionYEndIndex);
        
        std::string::size_type sz;
        return SVector2(std::stof(positionXAsString, &sz), std::stof(positionYAsString, &sz)); 
    }
};


namespace SMath 
{
    static SMat4 Translate(const SMat4& matrix, const glm::vec3& inVector) { return glm::translate(matrix, inVector); }
    static SMat4 Scale(const SMat4& matrix, const glm::vec3& inVector) { return glm::scale(matrix, inVector); }
    static SMat4 Rotate(const SMat4& matrix, const float& inFloat, const glm::vec3& rotationVector) { return glm::rotate(matrix, inFloat, rotationVector); }
    static SMat4 Inverse(const SMat4& matrix) { return glm::inverse(matrix); }
    static float Radians(const float rotation) { return glm::radians(rotation); }

    static float Clamp(const float value, const float min, const float max) { return std::clamp(value, min, max); }
}

