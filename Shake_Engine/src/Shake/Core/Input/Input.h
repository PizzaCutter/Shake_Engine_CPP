#pragma once
#include "KeyCodes.h"
#include "MouseCodes.h"

namespace Shake
{
    class Input
    {
    public:
        static bool IsKeyPressed(KeyCode keycode);

        static bool IsMouseButtonPressed(MouseCode mouseCode);
        static std::pair<float, float> GetMousePos();
        static float GetMouseX();
        static float GetMouseY();
    };
}
