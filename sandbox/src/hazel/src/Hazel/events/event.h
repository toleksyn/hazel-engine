#pragma once
#include "../core.h"
#include "../../hzpch.h"

namespace Hazel {

    enum class EventType {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    enum EventCategory {
        None = 0,
        EventCategoryApplication = BIT(1),
        EventCategoryInput = BIT(2),
        EventCategoryKeyboard = BIT(3),
        EventCategoryMouse = BIT(4),
        EventCategoryMouseButton = BIT(5)
    };

#define EVENT_CLASS_TYPE(type) static EventType getStaticType() { return EventType::type; }\
                                virtual EventType getEventType() const override { return getStaticType(); }\
                                virtual const char* getName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int getCategoryFlags() const override { return category; }

    class HAZEL_API Event {
        friend class EventDispatcher;
    public:
        virtual EventType getEventType() const = 0;
        virtual const char* getName() const = 0;
        virtual int getCategoryFlags() const = 0;
        virtual std::string toString() const { return getName(); }

        inline bool isInCategory(EventCategory category) {
            return getCategoryFlags() & category;
        }
    protected:
        bool m_Handled = false;
    };

    class EventDispatcher
    {
        template<typename T>
        using EventFn = std::function<bool(T&)>;
    public:
        EventDispatcher(Event& event)
            : m_Event(event)
        {
        }

        template<typename T>
        bool dispatch(EventFn<T> func)
        {
            if (m_Event.getEventType() == T::getStaticType())
            {
                m_Event.m_Handled = func(*(T*)&m_Event);
                return true;
            }
            return false;
        }
    private:
        Event& m_Event;
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& e)
    {
        return os << e.toString();
    }

}
