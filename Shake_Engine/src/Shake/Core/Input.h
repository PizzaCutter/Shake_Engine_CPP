#pragma once
#include "KeyCodes.h"
#include "MouseCodes.h"
#include "Shake/Core/Core.h"

namespace Shake
{
    class SHAKE_API Input
    {
    public:
        static bool IsKeyPressed(KeyCode keycode)
        {
            return s_Instance->IsKeyPressedImpl(keycode);
        }

        static bool IsMouseButtonPressed(MouseCode mouseCode) { return s_Instance->IsMouseButtonPressedImpl(mouseCode); }
        static std::pair<float, float> GetMousePos() { return s_Instance->GetMousePosImpl(); }
        static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
        static float GetMouseY() { return s_Instance->GetMouseYImpl(); }
        
    protected:
       virtual bool IsKeyPressedImpl(KeyCode keycode) = 0;

       virtual bool IsMouseButtonPressedImpl(MouseCode mouseCode) = 0;
       virtual std::pair<float, float> GetMousePosImpl() = 0;
       virtual float GetMouseXImpl() = 0;
       virtual float GetMouseYImpl() = 0;
    private:
        static Input* s_Instance;
    };
}
