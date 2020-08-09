#include "sepch.h"
#include "OrthographicCameraController.h"
#include "Shake/Core/Input.h"
#include "Shake/Events/ApplicationEvent.h"
#include "Shake/Events/MouseEvent.h"

namespace Shake
{
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)
    
    OrthographicCameraController::OrthographicCameraController(float aspectRatio)
        : m_aspectRatio(aspectRatio),
          m_orthoCamera(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel)
    {
        
    }

    inline float OrthographicCameraController::GetRelativeMovementSpeed() const
    {
       return m_movementSpeed * m_zoomLevel; 
    }
    inline float OrthographicCameraController::GetRelativeMouseMovementSpeed() const 
    {
       return m_mouseMovementSpeed * m_zoomLevel; 
    }

    void OrthographicCameraController::OnUpdate(Timestep timeStep)
    {
        if (Input::IsKeyPressed(KeyCode::W))
        {
            SVector3 pos = m_orthoCamera.GetPosition();
            pos += SVector3(0.0f, GetRelativeMovementSpeed(), 0.0f) * timeStep.GetSeconds();
            m_orthoCamera.SetPosition(pos);
        }
        if (Input::IsKeyPressed(KeyCode::S))
        {
            SVector3 pos = m_orthoCamera.GetPosition();
            pos += SVector3(0.0f, -GetRelativeMovementSpeed(), 0.0f) * timeStep.GetSeconds();
            m_orthoCamera.SetPosition(pos);
        }
        if (Input::IsKeyPressed(KeyCode::A))
        {
            SVector3 pos = m_orthoCamera.GetPosition();
            pos += SVector3(-GetRelativeMovementSpeed(), 0.0f, 0.0f) * timeStep.GetSeconds();
            m_orthoCamera.SetPosition(pos);
        }
        if (Input::IsKeyPressed(KeyCode::D))
        {
            SVector3 pos = m_orthoCamera.GetPosition();
            pos += SVector3(GetRelativeMovementSpeed(), 0.0f, 0.0f) * timeStep.GetSeconds();
            m_orthoCamera.SetPosition(pos);
        }

        if(Input::IsMouseButtonPressed(MouseCode::Button2))
        {
            const std::pair<float, float> mousePos = Input::GetMousePos();
            const float diffX = m_prevMousePosition.first - mousePos.first;
            const float diffY = mousePos.second - m_prevMousePosition.second;  
            SVector3 pos = m_orthoCamera.GetPosition();
            pos += SVector3(diffX * GetRelativeMouseMovementSpeed(), diffY * GetRelativeMouseMovementSpeed(), 0.0f) * timeStep.GetSeconds();
            m_orthoCamera.SetPosition(pos);
        } 
    }
    
    void OrthographicCameraController::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolledCallback));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OrthographicCameraController::OnWindowResizedCallback));
        dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FN(OrthographicCameraController::OnMouseMovedCallback));
    }

    bool OrthographicCameraController::OnMouseScrolledCallback(const MouseScrolledEvent& event)
    {
        m_zoomLevel -= event.GetYOffset() * m_zoomInSpeed;
        m_zoomLevel = std::clamp(m_zoomLevel, m_minZoomLevel, m_maxZoomLevel);
        m_orthoCamera.SetProjection(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel);
        return true;  
    }
    
    bool OrthographicCameraController::OnWindowResizedCallback(const WindowResizeEvent& event)
    {
        m_aspectRatio = static_cast<float>(event.GetWidth()) / static_cast<float>(event.GetHeight());
        m_orthoCamera.SetProjection(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel);
        return true; 
    }

    bool OrthographicCameraController::OnMouseMovedCallback(const MouseMovedEvent& e)
    {
        if(Input::IsMouseButtonPressed(MouseCode::Button0))
        {
       }
        
        m_prevMousePosition.first = e.GetX();
        m_prevMousePosition.second = e.GetY();
        return true; 
    }
}
