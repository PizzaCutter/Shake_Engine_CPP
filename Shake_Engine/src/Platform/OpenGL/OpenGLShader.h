#pragma once

#include "glm/fwd.hpp"
#include "Shake/Renderer/Shader.h"

namespace Shake
{
    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
        virtual ~OpenGLShader();

        void Bind() const override;
        void Unbind() const override;
        
        void UploadUniformInt(const std::string& name, int value) override;

        void UploadUniformMat3(const std::string& name, const glm::mat3& matrix) override;
        void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) override;

        void UploadUniformFloat(const std::string& name, float value) override;
        void UploadUniformFloat2(const std::string& name, const glm::vec2& data) override;
        void UploadUniformFloat3(const std::string& name, const glm::vec3& data) override;
        void UploadUniformFloat4(const std::string& name, const glm::vec4& vector) override;
        
    private:
        uint32_t m_ShaderId = -1;
    };
}
