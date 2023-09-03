#pragma once
#include "event.h"

namespace Hazel {

    class HAZEL_API KeyEvent : public Event
    {
    public:
        inline int getKeyCode() { return m_keyCode; }

        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryMouse)

    protected:
        KeyEvent (int keyCode)
            : m_keyCode(keyCode) {}
        int m_keyCode;
    };

    class HAZEL_API KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(int keyCode, int repeatCount)
            : KeyEvent(keyCode), m_repeatCount(repeatCount) {}

        EVENT_CLASS_TYPE(KeyPressed)

        inline int getRepeatCount() const { return m_repeatCount; }

        std::string toString() const override {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << m_keyCode << " (" << m_repeatCount << " repeats)";
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

        std::string toString() const override {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_keyCode;
            return ss.str();
        }
    };
}
