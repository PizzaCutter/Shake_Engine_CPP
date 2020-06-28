#pragma once

#include "Shake/Core/Layer.h"
#include "Shake/Events/KeyEvent.h"
#include "Shake/Events/MouseEvent.h"
#include "Shake/Events/ApplicationEvent.h"

namespace Shake
{
    class SHAKE_API ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnAttach() override;
        void OnDetach() override;

        void OnUpdate() override;
        void OnEvent(Event& event) override;
    private:
        bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& event);
        bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event);
        bool OnMouseMovedEvent(MouseMovedEvent& event);
        bool OnMouseScrolledEvent(MouseScrolledEvent& event);

        bool OnKeyPressedEvent(KeyPressedEvent& event);
        bool OnKeyReleasedEvent(KeyReleasedEvent& event);
        bool OnKeyTypedEvent(KeyTypedEvent& event);

        bool OnWindowResizeEvent(WindowResizeEvent& event);
    private:
        float m_Time = 0.0f;
    };
}
