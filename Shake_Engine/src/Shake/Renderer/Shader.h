#pragma once
#include "glm/fwd.hpp"
#include "Shake/Math/SMath.h"

namespace Shake
{
    class Shader
    {
    public:
        virtual ~Shader() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void UploadUniformInt(const std::string& name, int value) = 0;

        virtual void UploadUniformMat3(const std::string& name, const SMat3& matrix) = 0;
        virtual void UploadUniformMat4(const std::string& name, const SMat4& matrix) = 0;

        virtual void UploadUniformFloat(const std::string& name, float value) = 0;
        virtual void UploadUniformFloat2(const std::string& name, const SVector2& data) = 0;
        virtual void UploadUniformFloat3(const std::string& name, const SVector3& data) = 0;
        virtual void UploadUniformFloat4(const std::string& name, const SVector4& vector) = 0;


        static Shader* Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    };
}
