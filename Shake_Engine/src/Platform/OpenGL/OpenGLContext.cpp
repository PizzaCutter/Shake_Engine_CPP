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
        SE_CORE_ASSERT(status, "Failed to initialize GLAD!");

        auto vendor = glGetString(GL_VENDOR);
        SE_CORE_INFO("OpenGL Renderer: {0} {1}", vendor, glGetString(GL_RENDERER));
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_WindowHandle);
    }
}
