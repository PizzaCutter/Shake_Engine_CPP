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

        virtual SString GetName() const = 0;

        virtual void UploadUniformInt(const SString& name, int value) = 0;
        virtual void UploadUniformIntArray(const SString& name, int* values, uint32_t size) = 0;

        virtual void UploadUniformMat3(const SString& name, const SMat3& matrix) = 0;
        virtual void UploadUniformMat4(const SString& name, const SMat4& matrix) = 0;

        virtual void UploadUniformFloat(const SString& name, float value) = 0;
        virtual void UploadUniformFloat2(const SString& name, const SVector2& data) = 0;
        virtual void UploadUniformFloat3(const SString& name, const SVector3& data) = 0;
        virtual void UploadUniformFloat4(const SString& name, const SVector4& vector) = 0;

        static SharedPtr<Shader> Create(const SString& path);
    };

    class ShaderLibrary
    {
    public:
        void Load(const SString& filepath);
        
        SharedPtr<Shader> Get(const SString& shaderName);

    private:
        std::unordered_map<SString, SharedPtr<Shader>> m_shaderReferences;
    };
}
