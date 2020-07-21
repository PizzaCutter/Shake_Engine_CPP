#pragma once

namespace Shake
{
    class Shader
    {
    public:
        Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
        ~Shader();

        void Bind() const;
        void Unbind() const;
    private:
        unsigned int m_ShaderId;
    };
}
