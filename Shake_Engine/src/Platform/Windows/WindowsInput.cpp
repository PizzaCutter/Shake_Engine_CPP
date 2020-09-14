#include "sepch.h"

#include "Shake/Core/Input/Input.h"

#include "GLFW/glfw3.h"
#include "Shake/Window.h"
#include "Shake/Core/Application.h"
#include "Shake/Math/SMath.h"

namespace Shake
{
    bool Input::IsKeyPressed(KeyCode keycode)
    {
        GLFWwindow* glfwWindow = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        const int state = glfwGetKey(glfwWindow, static_cast<int>(keycode));
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool Input::IsKeyDown(KeyCode keycode)
    {
        GLFWwindow* glfwWindow = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        const int state = glfwGetKey(glfwWindow, static_cast<int>(keycode));
        return state == GLFW_PRESS;
    }

    bool Input::IsMouseButtonPressed(MouseCode mouseCode)
    {
        GLFWwindow* glfwWindow = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        const int state = glfwGetMouseButton(glfwWindow, static_cast<int>(mouseCode));
        return state == GLFW_PRESS;
    }

    SVector2 Input::GetMousePos()
    {
        GLFWwindow* glfwWindow = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        double xPos;
        double yPos;
        glfwGetCursorPos(glfwWindow, &xPos, &yPos); 
        return SVector2(static_cast<float>(xPos), static_cast<float>(yPos));
    }

    float Input::GetMouseX()
    {
        return GetMousePos().x;
    }

    float Input::GetMouseY()
    {
        return GetMousePos().y;
    }
}
