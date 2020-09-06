#pragma once

#include "Shake/Renderer/Shader.h"
#include "glm/fwd.hpp"

typedef unsigned int GLenum;

namespace Shake
{
    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const SString& filePath);
        virtual ~OpenGLShader();

        void Bind() const override;
        void Unbind() const override;
        SString GetName() const override { return m_name; } 

        void UploadUniformInt(const SString& name, int value) override;
        void UploadUniformIntArray(const SString& name, int* values, uint32_t size) override;

        void UploadUniformMat3(const SString& name, const SMat3& matrix) override;
        void UploadUniformMat4(const SString& name, const SMat4& matrix) override;

        void UploadUniformFloat(const SString& name, float value) override;
        void UploadUniformFloat2(const SString& name, const SVector2& data) override;
        void UploadUniformFloat3(const SString& name, const SVector3& data) override;
        void UploadUniformFloat4(const SString& name, const SVector4& vector) override;

    private:
        uint32_t m_ShaderId = -1;
        SString m_name = ""; 

        SString ReadFile(const SString& filePath);
        std::unordered_map<GLenum, SString> PreProcess(const SString& source);
        void Compile(std::unordered_map<GLenum, SString> input);

        static GLenum GetShaderTypeFromString(const SString& shaderTypeAsString);
    };
}
