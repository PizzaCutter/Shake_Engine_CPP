#pragma once

#include <sstream>

#include "Shake/Events/Event.h"

namespace Shake
{
    class WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent(unsigned int width, unsigned int height) : Width(width), Height(height)
        {
            
        }

        unsigned int GetWidth() { return Width; }
        unsigned int GetHeight() { return Height; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "WindowResizeEvent: " << Width << ", " << Height;
            return ss.str();
        }

        EventType GetEventType() const override { return EventType::WindowResize; }
        int GetCategoryFlags() const override { return EventCategoryApplication; };
    private:
        unsigned int Width;
        unsigned int Height;
    };

    class WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent() = default;

        EventType GetEventType() const override { return EventType::WindowClose; };
        int GetCategoryFlags() const override { return EventCategoryApplication; };
    };

    class AppTickEvent : public Event
    {
    public:
        AppTickEvent() = default;

        EventType GetEventType() const override { return EventType::AppTick; };
        int GetCategoryFlags() const override { return EventCategoryApplication; };
    };

    class AppUpdateEvent : public Event
    {
    public:
        AppUpdateEvent() = default;

        EventType GetEventType() const override { return EventType::AppUpdate; };
        int GetCategoryFlags() const override { return EventCategoryApplication; };
    };

    class AppRenderEvent : public Event
    {
    public:
        AppRenderEvent() = default;

        EventType GetEventType() const override { return EventType::AppRender; }
        int GetCategoryFlags() const override { return EventCategoryApplication; };
    };
}