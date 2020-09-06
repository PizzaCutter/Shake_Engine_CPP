#include "sepch.h"
#include "OpenGLShader.h"

#include <fstream>
#include <vector>

#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"
#include "Shake/Core/Log.h"
#include "Shake/Helpers/FileReader.h"

namespace Shake
{
    OpenGLShader::OpenGLShader(const std::string& filePath)
    {
        const std::string fileAsString = ReadFile(filePath);
        const std::unordered_map<GLenum, std::string> processedData = PreProcess(fileAsString);
        Compile(processedData);

        // Contents/Shaders/Texture.glsl extract name from this
        const size_t lastSlash = filePath.find_last_of("/");
        const size_t lastDot = filePath.find_last_of(".");
        const size_t beginIndex = lastSlash + 1;
        m_name = filePath.substr(beginIndex, lastDot - beginIndex);
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

    void OpenGLShader::UploadUniformInt(const std::string& name, const int value)
    {
         GLint uniformLocation = glGetUniformLocation(m_ShaderId, name.c_str());
         glUniform1i(uniformLocation, value);
    }

    void OpenGLShader::UploadUniformIntArray(const std::string& name, int* values, uint32_t size)
    {
        GLint uniformLocation = glGetUniformLocation(m_ShaderId, name.c_str());
        glUniform1iv(uniformLocation, size, values);
    }

    void OpenGLShader::UploadUniformMat3(const std::string& name, const SMat3& matrix)
    {
        GLint uniformLocation = glGetUniformLocation(m_ShaderId, name.c_str());
        glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void OpenGLShader::UploadUniformMat4(const std::string& name, const SMat4& matrix)
    {
        GLint uniformLocation = glGetUniformLocation(m_ShaderId, name.c_str());
        glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void OpenGLShader::UploadUniformFloat(const std::string& name, float value)
    {
         GLint uniformLocation = glGetUniformLocation(m_ShaderId, name.c_str());
         glUniform1f(uniformLocation, value);
    }

    void OpenGLShader::UploadUniformFloat2(const std::string& name, const SVector2& data)
    {
        GLint uniformLocation = glGetUniformLocation(m_ShaderId, name.c_str());
        glUniform2f(uniformLocation, data.x, data.y);
    }

    void OpenGLShader::UploadUniformFloat3(const std::string& name, const SVector3& data)
    {
        GLint uniformLocation = glGetUniformLocation(m_ShaderId, name.c_str());
        glUniform3f(uniformLocation, data.x, data.y, data.z);
    }

    void OpenGLShader::UploadUniformFloat4(const std::string& name, const SVector4& vector)
    {
        GLint uniformLocation = glGetUniformLocation(m_ShaderId, name.c_str());
        glUniform4f(uniformLocation, vector.x, vector.y, vector.z, vector.w);
    }

    std::string OpenGLShader::ReadFile(const std::string& filePath)
    {
        std::string result;
        std::ifstream in(filePath, std::ios::in | std::ios::binary);
        if(in)
        {
            in.seekg(0, std::ios::end);
            result.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&result[0], result.size());
            in.close();
        }else
        {
            SE_ENGINE_LOG(LogVerbosity::Error, "Could not open file '{0}'", filePath);
        }
        return result;
    }

    GLenum OpenGLShader::GetShaderTypeFromString(const std::string& shaderTypeAsString)
    {
        if(shaderTypeAsString == "vertex")
        {
            return GL_VERTEX_SHADER;
        }
        if(shaderTypeAsString == "fragment" || shaderTypeAsString == "pixel")
        {
            return GL_FRAGMENT_SHADER;
        }
        return GL_VERTEX_SHADER; 
    }
    
    std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
    {
        std::unordered_map<GLenum, std::string> thing = {};
        
        const std::string typeThing = "#type"; 

        size_t index = 0;
        while(index != std::string::npos)
        {
            const std::string::size_type foundIndex = source.find(typeThing, index) + typeThing.length();
            const std::string::size_type endOfTypeIndex = source.find("\r", index);
            const std::string::size_type nextShaderIndex = source.find(typeThing, endOfTypeIndex);

            std::string shaderTypeString = source.substr(foundIndex + 1, endOfTypeIndex - (foundIndex + 1));
            const std::string shaderSource = source.substr(endOfTypeIndex, nextShaderIndex - endOfTypeIndex);

            const GLenum shaderType = GetShaderTypeFromString(shaderTypeString);
            //TODO[rsmekens]: check shader types 

            thing.emplace(shaderType, shaderSource);

            index = nextShaderIndex;
        } 
        return thing;
    }
    
    void OpenGLShader::Compile(std::unordered_map<GLenum, std::string> input)
    {
        GLuint program = glCreateProgram();
        std::vector<GLuint> openGLShaders;
        openGLShaders.reserve(input.size());
        
        for (auto& shaderInput: input)
        {
            // Create an empty vertex shader handle
            const GLuint openGLShader = glCreateShader(shaderInput.first);
            openGLShaders.push_back(openGLShader);

            // Send the vertex shader source code to GL
            // Note that std::string's .c_str is NULL character terminated.
            const GLchar* source = shaderInput.second.c_str();
            glShaderSource(openGLShader, 1, &source, 0);

            // Compile the vertex shader
            glCompileShader(openGLShader);

            GLint isCompiled = 0;
            glGetShaderiv(openGLShader, GL_COMPILE_STATUS, &isCompiled);
            if(isCompiled == GL_FALSE)
            {
                GLint maxLength = 0;
                glGetShaderiv(openGLShader, GL_INFO_LOG_LENGTH, &maxLength);

                // The maxLength includes the NULL character
                std::vector<GLchar> infoLog(maxLength);
                glGetShaderInfoLog(openGLShader, maxLength, &maxLength, &infoLog[0]);

                // We don't need the shader anymore.
                glDeleteShader(openGLShader);

                SE_ENGINE_LOG(LogVerbosity::Error,"{0}", infoLog.data());
                SE_CORE_ASSERT(false, "Vertex shader compilation failure!");
                return;
            }
        }

        // Only initialize this once compilation has succeeded
        m_ShaderId = program;

        // Attach our shaders to our program
        for (auto& element : openGLShaders)
        {
            glAttachShader(program, element);
        }

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
            for (auto& element : openGLShaders)
            {
                glDeleteShader(element);
            }

            SE_ENGINE_LOG(LogVerbosity::Error,"{0}", infoLog.data());
            SE_CORE_ASSERT(false, "OpenGLShader link failure!");

            return;
        }

        // Always detach shaders after a successful link.
        for (auto& element : openGLShaders)
        {
            glDetachShader(program, element);
        }
    }
}
