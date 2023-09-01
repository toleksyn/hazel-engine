#include "../hzpch.h"
#include "application.h"
#include "events/applicationEvent.h"
#include "log.h"
#include "GLFW/glfw3.h"

namespace Hazel {

    Application::Application()
    {
        m_Window = std::unique_ptr<Window>(Window::create());
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
}
