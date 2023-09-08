#pragma once

#include "event.h"

namespace Hazel {

    class HAZEL_API KeyEvent : public Event
    {
    public:
        inline int RetKeyCode() { return m_KeyCode; }

        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryMouse)

    protected:
        KeyEvent (int keyCode)
            : m_KeyCode(keyCode) {}
        int m_KeyCode;
    };

    class HAZEL_API KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(int keyCode, int repeatCount)
            : KeyEvent(keyCode), m_repeatCount(repeatCount) {}

        EVENT_CLASS_TYPE(KeyPressed)

        inline int GetRepeatCount() const { return m_repeatCount; }
        
        std::string ToString() const override {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_repeatCount << " repeats)";
            return ss.str();
        }

    private:
        int m_repeatCount;
    };


    class HAZEL_API KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(int keyCode)
            : KeyEvent(keyCode){}

        EVENT_CLASS_TYPE(KeyReleased)
        
        std::string ToString() const override {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_KeyCode;
            return ss.str();
        }
    };
}
