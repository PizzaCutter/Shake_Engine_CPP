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
        
        void UploadUniformInt(const std::string& name, int value);

        void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
        void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

        void UploadUniformFloat(const std::string& name, float value);
        void UploadUniformFloat2(const std::string& name, const glm::vec2& data);
        void UploadUniformFloat3(const std::string& name, const glm::vec3& data);
        void UploadUniformFloat4(const std::string& name, const glm::vec4& vector);
        
    private:
        uint32_t m_ShaderId = -1;
    };
}
