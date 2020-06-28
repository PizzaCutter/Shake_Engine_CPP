#include "sepch.h"
#include "WindowsInput.h"

#include "Shake/Window.h"
#include "Shake/Core/Application.h"

namespace Shake
{
    Input* Input::s_Instance = new WindowsInput();
    
    bool WindowsInput::IsKeyPressedImpl(KeyCode keycode)
    {
        GLFWwindow* glfwWindow = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        const int state = glfwGetKey(glfwWindow, static_cast<int>(keycode));
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool WindowsInput::IsMouseButtonPressedImpl(MouseCode mouseCode)
    {
        GLFWwindow* glfwWindow = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        const int state = glfwGetMouseButton(glfwWindow, static_cast<int>(mouseCode));
        return state == GLFW_PRESS;
    }

    std::pair<float, float> WindowsInput::GetMousePosImpl()
    {
        GLFWwindow* glfwWindow = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        double xPos;
        double yPos;
        glfwGetCursorPos(glfwWindow, &xPos, &yPos); 
        return std::make_pair<float, float>(static_cast<float>(xPos), static_cast<float>(yPos));
    }

    float WindowsInput::GetMouseXImpl()
    {
        return GetMousePosImpl().first;
    }

    float WindowsInput::GetMouseYImpl()
    {
        return GetMousePosImpl().second;
    }
}
