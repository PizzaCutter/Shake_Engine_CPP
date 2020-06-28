#pragma once
#include "Shake/Core/Input.h"

#include <GLFW/glfw3.h>

namespace Shake
{
    class WindowsInput : public Input
    {
    protected:
        bool IsKeyPressedImpl(KeyCode keycode) override;
        bool IsMouseButtonPressedImpl(MouseCode mouseCode) override;
        std::pair<float, float> GetMousePosImpl() override;
        float GetMouseXImpl() override;
        float GetMouseYImpl() override;
    };
}
