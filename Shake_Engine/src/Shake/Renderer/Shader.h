#pragma once
#include "glm/fwd.hpp"
#include "Shake/Core/Core.h"
#include "Shake/Math/SMath.h"

namespace Shake
{
    class Shader
    {
    public:
        virtual ~Shader() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual std::string GetName() const = 0;

        virtual void UploadUniformInt(const std::string& name, int value) = 0;
        virtual void UploadUniformIntArray(const std::string& name, int* values, uint32_t size) = 0;

        virtual void UploadUniformMat3(const std::string& name, const SMat3& matrix) = 0;
        virtual void UploadUniformMat4(const std::string& name, const SMat4& matrix) = 0;

        virtual void UploadUniformFloat(const std::string& name, float value) = 0;
        virtual void UploadUniformFloat2(const std::string& name, const SVector2& data) = 0;
        virtual void UploadUniformFloat3(const std::string& name, const SVector3& data) = 0;
        virtual void UploadUniformFloat4(const std::string& name, const SVector4& vector) = 0;

        static SharedPtr<Shader> Create(const std::string& path);
    };

    class ShaderLibrary
    {
    public:
        void Load(const std::string& filepath);
        
        SharedPtr<Shader> Get(const std::string& shaderName);

    private:
        std::unordered_map<std::string, SharedPtr<Shader>> m_shaderReferences;
    };
}
