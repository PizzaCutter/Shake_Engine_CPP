#pragma once

#include <sstream>

#include "Shake/Events/Event.h"
#include "Shake/Core/KeyCodes.h"

namespace Shake
{
    class KeyEvent : public Event
    {
    public:
        KeyEvent(KeyCode keyCode) : m_keyCode(keyCode) { }

        KeyCode GetKeyCode() const { return m_keyCode; }

        int GetCategoryFlags() const override { return EventCategoryKeyboard | EventCategoryInput; };

    protected:
        KeyCode m_keyCode;
    };

    class KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(KeyCode keycode, int repeatCount) : KeyEvent(keycode), m_repeatCount(repeatCount)
        {
        }

        EventType GetEventType() const override { return EventType::KeyPressed; }

        int GetRepeatCount() const { return m_repeatCount; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << m_keyCode << " (" << m_repeatCount << " repeats)";
            return ss.str();
        }

    private:
        int m_repeatCount;
    };

    class KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(KeyCode keycode) : KeyEvent(keycode)
        {
        }

        EventType GetEventType() const override { return EventType::KeyReleased; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_keyCode;
            return ss.str();
        }
    };
}
