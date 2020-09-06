#pragma once
#include "OrthographicCamera.h"
#include "Shake/Events/ApplicationEvent.h"
#include "Shake/Events/Event.h"
#include "Shake/Events/MouseEvent.h"

namespace Shake
{
    class Timestep;

    class OrthographicCameraController
    {
    public:
        OrthographicCameraController(float aspectRatio);

        void OnUpdate(Timestep timeStep);
        void OnEvent(Event& e);

        void OnResize(float width, float height);

        OrthographicCamera& GetCamera() { return m_orthoCamera; }

    private:
        bool OnMouseScrolledCallback(const MouseScrolledEvent& event);
        bool OnWindowResizedCallback(const WindowResizeEvent& event);
        bool OnMouseMovedCallback(const MouseMovedEvent& e);

        float m_aspectRatio = 1.9f;
        float m_zoomLevel = 1.0f;
        OrthographicCamera m_orthoCamera;
        
        float m_minZoomLevel = 0.1f;
        float m_maxZoomLevel = 10.0f;

        float m_movementSpeed = 3.0f;
        float m_mouseMovementSpeed = 0.1f;
        float m_zoomInSpeed = 0.1f;

        float GetRelativeMovementSpeed() const;
        float GetRelativeMouseMovementSpeed() const;

        std::pair<float, float> m_prevMousePosition;
    };
}
