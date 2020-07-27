#pragma once

#include "glm/glm.hpp"

namespace Shake
{
    class Shader
    {
    public:
        Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
        ~Shader();

        void Bind() const;
        void Unbind() const;

        void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
    private:
        unsigned int m_ShaderId;
    };
}
