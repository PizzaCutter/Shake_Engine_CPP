#pragma once

#include "Shake/Events/Event.h"
#include "Shake/Core/Input/MouseCodes.h"

namespace Shake
{
    class MouseMovedEvent : public Event
    {
    public:
        MouseMovedEvent(float x, float y) : m_mouseX(x), m_mouseY(y) {}

        float GetX() const { return m_mouseX; }
        float GetY() const { return m_mouseY; }

        static EventType GetStaticType() { return EventType::MouseMoved; } 
        
        EventType GetEventType() const override { return EventType::MouseMoved; };
        int GetCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput; };
        
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << m_mouseX << ", " << m_mouseY;
            return ss.str();
        }
        
    private:
        float m_mouseX, m_mouseY;
    };

    class MouseScrolledEvent : public Event
    {
    public:
        MouseScrolledEvent(float xOffset, float yOffset) : m_xOffset(xOffset), m_yOffset(yOffset) {}

        float GetXOffset() const { return m_xOffset; }
        float GetYOffset() const { return m_yOffset; }

        static EventType GetStaticType() { return EventType::MouseScrolled; }
        
        EventType GetEventType() const override { return EventType::MouseScrolled; }
        int GetCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput; }
        
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
            return ss.str();
        }
        
    private:
        float m_xOffset;
        float m_yOffset;
    };

    class MouseButtonEvent : public Event
    {
    public:
        MouseButtonEvent(MouseCode button) : m_button(button) {}
        
        MouseCode GetMouseButton() const { return m_button;}

        int GetCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput; };
    protected:
        MouseCode m_button;
    };

    class MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(MouseCode button) : MouseButtonEvent(button) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << m_button;
            return ss.str();
        }

        static EventType GetStaticType() { return EventType::MouseButtonPressed; }
        EventType GetEventType() const override { return EventType::MouseButtonPressed; };
    };
    
    class MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(MouseCode button) : MouseButtonEvent(button) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << m_button;
            return ss.str();
        }
        
        static EventType GetStaticType() { return EventType::MouseButtonReleased; }
        EventType GetEventType() const override { return EventType::MouseButtonReleased; }
    };
}