#pragma once

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale

#define SVector2 glm::vec2
#define SVector3 glm::vec3
#define SVector4 glm::vec4

#define SMat3 glm::mat3
#define SMat4 glm::mat4

namespace SMath 
{
    static SMat4 Translate(const SMat4& matrix, const SVector3& inVector) { return glm::translate(matrix, inVector); }
    static SMat4 Scale(const SMat4& matrix, const SVector3& inVector) { return glm::scale(matrix, inVector); }
    static SMat4 Rotate(const SMat4& matrix, const float& inFloat, const SVector3& rotationVector) { return glm::rotate(matrix, inFloat, rotationVector); }
    static SMat4 Inverse(const SMat4& matrix) { return glm::inverse(matrix); }
    static float Radians(const float rotation) { return glm::radians(rotation); }
}

