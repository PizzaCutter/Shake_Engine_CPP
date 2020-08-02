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

        void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
        void UploadUniformFloat4(const std::string& name, const glm::vec4& vector);

        void UploadUniformFloat3(const std::string& name, const glm::vec3& data);
        
    private:
        uint32_t m_ShaderId = -1;
    };
}
