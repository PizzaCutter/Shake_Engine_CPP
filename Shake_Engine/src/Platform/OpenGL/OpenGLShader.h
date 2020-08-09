#pragma once

#include "Shake/Renderer/Shader.h"
#include "glm/fwd.hpp"

typedef unsigned int GLenum;

namespace Shake
{
    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string& filePath);
        virtual ~OpenGLShader();

        void Bind() const override;
        void Unbind() const override;
        
        void UploadUniformInt(const std::string& name, int value) override;

        void UploadUniformMat3(const std::string& name, const SMat3& matrix) override;
        void UploadUniformMat4(const std::string& name, const SMat4& matrix) override;

        void UploadUniformFloat(const std::string& name, float value) override;
        void UploadUniformFloat2(const std::string& name, const SVector2& data) override;
        void UploadUniformFloat3(const std::string& name, const SVector3& data) override;
        void UploadUniformFloat4(const std::string& name, const SVector4& vector) override;

    private:
        uint32_t m_ShaderId = -1;

        std::string ReadFile(const std::string& filePath);
        std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
        void Compile(std::unordered_map<GLenum, std::string> input);

        static GLenum GetShaderTypeFromString(const std::string& shaderTypeAsString);
    };
}
