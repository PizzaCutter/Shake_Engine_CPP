#include "sepch.h"
#include "WindowsWindow.h"

#include "GLFW/glfw3.h"
#include "Platform/OpenGL/OpenGLContext.h"

#include "Shake/Events/ApplicationEvent.h"
#include "Shake/Events/KeyEvent.h"
#include "Shake/Events/MouseEvent.h"

namespace Shake
{
    static bool s_GLFWInitialized = false;

    static void GLFWErrorCallback(int error, const char* description)
    {
        //SE_CORE_ERROR("GLFW Error '{0}': '{1}'", error, description); 
    }

    Window* Window::Create(const WindowProps& props)
    {
        return new WindowsWindow(props);
    }

    WindowsWindow::WindowsWindow(const WindowProps& props)
    {
        Init(props);
    }

    WindowsWindow::~WindowsWindow()
    {
        Shutdown();
    }

    void WindowsWindow::Init(const Shake::WindowProps& props)
    {
        m_Data.Title = props.Title;
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;

        // TODO[rsmekens]: add logging

        if (!s_GLFWInitialized)
        {
            int success = glfwInit();

            //SE_CORE_ASSERT(success, "Could not initialize GLFW!");
            glfwSetErrorCallback(GLFWErrorCallback);

            s_GLFWInitialized = true;
        }

        m_Window = glfwCreateWindow(static_cast<int>(props.Width), static_cast<int>(props.Height), m_Data.Title.c_str(),
                                    nullptr, nullptr);

        m_Context = new OpenGLContext(m_Window);
        m_Context->Init();

        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(true);

        // SET GLFW callback
        SetupGLFWWindowCallbacks(); 
    }

    void WindowsWindow::SetupGLFWWindowCallbacks() const
    {
        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.Width = width;
            data.Height = height;

            WindowResizeEvent event(width, height);
            data.EventCallback(event);
        });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.EventCallback(event);
        });

        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
            case GLFW_PRESS:
                {
                    KeyPressedEvent event(KeyCode(key), 0);
                    data.EventCallback(event);
                    break;
                }
            case GLFW_REPEAT:
                {
                    KeyPressedEvent event(KeyCode(key), 1);
                    data.EventCallback(event);
                    break;
                }
            case GLFW_RELEASE:
                {
                    KeyReleasedEvent event = KeyReleasedEvent(KeyCode(key));
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int c)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            KeyTypedEvent event = KeyTypedEvent(KeyCode(c));
            data.EventCallback(event);
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
            case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event = MouseButtonPressedEvent(MouseCode(button));
                    data.EventCallback(event);
                    break;
                }
            case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event = MouseButtonReleasedEvent(MouseCode(button));
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseScrolledEvent event((float)xOffset, (float)yOffset);
            data.EventCallback(event);
        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseMovedEvent event((float)xPos, (float)yPos);
            data.EventCallback(event);
        });
    }

    void WindowsWindow::Shutdown()
    {
        if (m_Window != nullptr)
        {
            glfwDestroyWindow(m_Window);
        }
    }

    void WindowsWindow::OnUpdate()
    {
        glfwPollEvents();
        m_Context->SwapBuffers();
    }

    void WindowsWindow::SetVSync(bool enabled)
    {
        if (enabled)
        {
            glfwSwapInterval(1);
        }
        else
        {
            glfwSwapInterval(0);
        }
        m_Data.VSync = enabled;
    }

    bool WindowsWindow::IsVSync() const
    {
        return m_Data.VSync;
    }
}
