#include "sepch.h"
#include "OpenGLShader.h"

#include <vector>


#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"
#include "Shake/Core/Log.h"
#include "Shake/Helpers/FileReader.h"

namespace Shake
{
    OpenGLShader::OpenGLShader(const std::string& vertexOpenGLShaderPath, const std::string& fragmentOpenGLShaderPath)
    {
        const std::string vertexOpenGLShaderSource = FileReader::ReadFile("Shaders/" + vertexOpenGLShaderPath);
        const std::string fragmentOpenGLShaderSource = FileReader::ReadFile("Shaders/" + fragmentOpenGLShaderPath);

        // Create an empty vertex shader handle
        GLuint vertexOpenGLShader = glCreateShader(GL_VERTEX_SHADER);

        // Send the vertex shader source code to GL
        // Note that std::string's .c_str is NULL character terminated.
        const GLchar* source = vertexOpenGLShaderSource.c_str();
        glShaderSource(vertexOpenGLShader, 1, &source, 0);

        // Compile the vertex shader
        glCompileShader(vertexOpenGLShader);

        GLint isCompiled = 0;
        glGetShaderiv(vertexOpenGLShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(vertexOpenGLShader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(vertexOpenGLShader, maxLength, &maxLength, &infoLog[0]);

            // We don't need the shader anymore.
            glDeleteShader(vertexOpenGLShader);

            SE_CORE_ERROR("{0}", infoLog.data());
            SE_CORE_ASSERT(false, "Vertex shader compilation failure!");
            return;
        }

        // Create an empty fragment shader handle
        GLuint fragmentOpenGLShader = glCreateShader(GL_FRAGMENT_SHADER);

        // Send the fragment shader source code to GL
        // Note that std::string's .c_str is NULL character terminated.
        source = fragmentOpenGLShaderSource.c_str();
        glShaderSource(fragmentOpenGLShader, 1, &source, 0);

        // Compile the fragment shader
        glCompileShader(fragmentOpenGLShader);

        glGetShaderiv(fragmentOpenGLShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(fragmentOpenGLShader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(fragmentOpenGLShader, maxLength, &maxLength, &infoLog[0]);

            // We don't need the shader anymore.
            glDeleteShader(fragmentOpenGLShader);
            // Either of them. Don't leak shaders.
            glDeleteShader(vertexOpenGLShader);

            SE_CORE_ERROR("{0}", infoLog.data());
            SE_CORE_ASSERT(false, "Fragment shader compilation failure!");
            return;
        }

        // Vertex and fragment shaders are successfully compiled.
        // Now time to link them together into a program.
        // Get a program object.
        m_ShaderId = glCreateProgram();
        GLuint program = m_ShaderId;

        // Attach our shaders to our program
        glAttachShader(program, vertexOpenGLShader);
        glAttachShader(program, fragmentOpenGLShader);

        // Link our program
        glLinkProgram(program);

        // Note the different functions here: glGetProgram* instead of glGetOpenGLShader*.
        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

            // We don't need the program anymore.
            glDeleteProgram(program);
            // Don't leak shaders either.
            glDeleteShader(vertexOpenGLShader);
            glDeleteShader(fragmentOpenGLShader);

            SE_CORE_ERROR("{0}", infoLog.data());
            SE_CORE_ASSERT(false, "OpenGLShader link failure!");

            return;
        }

        // Always detach shaders after a successful link.
        glDetachShader(program, vertexOpenGLShader);
        glDetachShader(program, fragmentOpenGLShader);
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(m_ShaderId);
    }

    void OpenGLShader::Bind() const
    {
        glUseProgram(m_ShaderId);
    }

    void OpenGLShader::Unbind() const
    {
        glUseProgram(0);
    }

    void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
    {
        GLint uniformLocation = glGetUniformLocation(m_ShaderId, name.c_str());
        glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
    {
        GLint uniformLocation = glGetUniformLocation(m_ShaderId, name.c_str());
        glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& data)
    {
        GLint uniformLocation = glGetUniformLocation(m_ShaderId, name.c_str());
        glUniform3f(uniformLocation, data.x, data.y, data.z);
    }

    void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& vector)
    {
        GLint uniformLocation = glGetUniformLocation(m_ShaderId, name.c_str());
        glUniform4f(uniformLocation, vector.x, vector.y, vector.z, vector.w);
    }
}
