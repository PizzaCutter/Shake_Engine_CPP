#include "sepch.h"
#include "OpenGLContext.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "Shake/Core/Core.h"
#include "Shake/Core/Log.h"

namespace Shake
{
    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
    {
        m_WindowHandle = windowHandle; 
    }

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(m_WindowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        SE_ENGINE_LOG(LogVerbosity::Error, std::to_string(status), "Failed to initialize GLAD!");

        auto vendor = glGetString(GL_VENDOR);
        SELOG(LogVerbosity::Info, "OpenGL Renderer: {0} {1}", vendor, glGetString(GL_RENDERER));
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_WindowHandle);
    }
}
