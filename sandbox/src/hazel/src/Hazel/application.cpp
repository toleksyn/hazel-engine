#include "../hzpch.h"
#include "application.h"
#include "events/applicationEvent.h"
#include "log.h"
#include "GLFW/glfw3.h"

namespace Hazel {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application::Application()
    {
        m_Window = std::unique_ptr<Window>(Window::create());
        m_Window->setEventCallback(BIND_EVENT_FN(onEvent));
    }

    Application::~Application()
    {

    }

    void Application::run()
    {
        while (m_Running)
        {
            glClearColor(1, 0, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            m_Window->onUpdate();
        }
    }

    void Application::onEvent(Event &e)
    {
        HZ_CORE_INFO("{0}", e);
    }
}
