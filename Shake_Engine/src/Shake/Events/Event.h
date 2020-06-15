#pragma once

#include "Shake/Core/Core.h"

#include <string>
#include <functional>

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

    class SHAKE_API Event
    {
        friend class EventDispatcher;
    public:
        virtual EventType GetEventType() const = 0;
        const char* GetName() const
        {
            switch(GetEventType())
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
            }
            return "NOT IMPLEMENTED";
        };
        virtual std::string ToString() const { return GetName(); };
        virtual int GetCategoryFlags() const = 0;

        inline bool IsInCategory(EventCategory category)
        {
            return GetCategoryFlags() & category;
        }

    protected:
        bool Handled = false;
    };

    class EventDispatcher
    {
    public:
        EventDispatcher(Event& event) : Event(event)
        {
            
        }
        
        template<typename T, typename F>
        bool Dispatch(const F& func)
        {
            if(Event.GetEventType() == T::GetStaticType())
            {
                Event.Handled = func(static_cast<T&>(Event));
                return true;
            }
            return false;
        }
    private:
        Event& Event;
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& event)
    {
        return os << event.ToString();
    }
}
