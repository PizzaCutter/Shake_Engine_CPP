#include "sepch.h"

#include "Shake/Core/Input/Input.h"

#include "GLFW/glfw3.h"
#include "Shake/Window.h"
#include "Shake/Core/Application.h"

namespace Shake
{
    bool Input::IsKeyPressed(KeyCode keycode)
    {
        GLFWwindow* glfwWindow = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        const int state = glfwGetKey(glfwWindow, static_cast<int>(keycode));
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool Input::IsMouseButtonPressed(MouseCode mouseCode)
    {
        GLFWwindow* glfwWindow = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        const int state = glfwGetMouseButton(glfwWindow, static_cast<int>(mouseCode));
        return state == GLFW_PRESS;
    }

    std::pair<float, float> Input::GetMousePos()
    {
        GLFWwindow* glfwWindow = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        double xPos;
        double yPos;
        glfwGetCursorPos(glfwWindow, &xPos, &yPos); 
        return std::make_pair<float, float>(static_cast<float>(xPos), static_cast<float>(yPos));
    }

    float Input::GetMouseX()
    {
        return GetMousePos().first;
    }

    float Input::GetMouseY()
    {
        return GetMousePos().second;
    }
}
