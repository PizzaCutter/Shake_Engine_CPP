#pragma once

#include "Shake/Core/Core.h"
#include "Shake/Strings/SString.h"

namespace Shake
{
    enum class EventType
    {
        None = 0,
        WindowClose,
        WindowResize,
        WindowFocus,
        WindowLostFocus,
        WindowMoved,
        AppTick,
        AppUpdate,
        AppRender,
        KeyPressed,
        KeyTyped,
        KeyReleased,
        MouseButtonPressed,
        MouseButtonReleased,
        MouseMoved,
        MouseScrolled
    };

    enum EventCategory
    {
        None = 0,
        EventCategoryApplication = BIT(0),
        EventCategoryInput = BIT(1),
        EventCategoryKeyboard = BIT(2),
        EventCategoryMouse = BIT(3),
        EventCategoryMouseButton = BIT(4)
    };
    
    class Event
    {
        friend class EventDispatcher;
    public:
        virtual ~Event() {};
        
        virtual EventType GetEventType() const = 0;

        virtual int GetCategoryFlags() const = 0;

        const char* GetName() const
        {
            switch (GetEventType())
            {
            case EventType::None: return "None";
            case EventType::WindowClose: return "WindowClose";
            case EventType::WindowResize: return "WindowResize";
            case EventType::WindowFocus: return "WindowFocus";
            case EventType::WindowLostFocus: return "WindowLostFocus";
            case EventType::WindowMoved: return "WindowMoved";
            case EventType::AppTick: return "AppTick";
            case EventType::AppUpdate: return "AppUpdate";
            case EventType::AppRender: return "AppRender";
            case EventType::KeyPressed: return "KeyPressed";
            case EventType::KeyReleased: return "KeyReleased";
            case EventType::MouseButtonPressed: return "MouseButtonPressed";
            case EventType::MouseButtonReleased: return "MouseButtonReleased";
            case EventType::MouseMoved: return "MouseMoved";
            case EventType::MouseScrolled: return "MouseScrolled";
            default: ;
            }
            return "NOT IMPLEMENTED";
        };
        virtual SString ToString() const { return GetName(); };

        bool IsInCategory(EventCategory category) const
        {
            return GetCategoryFlags() & category;
        }

        bool Handled = false;
    };

    class EventDispatcher
    {
    public:
        EventDispatcher(Event& event) : m_Event(event)
        {
        }

        template <typename T, typename F>
        bool Dispatch(const F& func)
        {
            if (m_Event.GetEventType() == T::GetStaticType())
            {
                 m_Event.Handled = func(static_cast<T&>(m_Event));
                 return true;
            }
            return false;
        }

    private:
        Event& m_Event;
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& event)
    {
        return os << event.ToString();
    }
}
