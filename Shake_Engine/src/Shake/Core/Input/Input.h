#pragma once
#include "KeyCodes.h"
#include "MouseCodes.h"
#include "Shake/Math/SMath.h"

namespace Shake
{
    class Input
    {
    public:
        static bool IsKeyPressed(KeyCode keycode);
        static bool IsKeyDown(KeyCode keycode);

        static bool IsMouseButtonPressed(MouseCode mouseCode);
        static SVector2 GetMousePos();
        static float GetMouseX();
        static float GetMouseY();
    };
}
