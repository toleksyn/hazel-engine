#include "unixwindow.h"
#include "../../Hazel/log.h"
#include "../../Hazel/events/applicationEvent.h"
#include "../../Hazel/events/mouseEvent.h"
#include "../../Hazel/events/keyEvent.h"

namespace Hazel {

    static bool s_GLFWInitialized = false;

    Window* Window::create(const WindowProps& props)
    {
        return new UnixWindow(props);
    }

    UnixWindow::UnixWindow(const WindowProps &props)
    {
        init(props);
    }

    UnixWindow::~UnixWindow()
    {
        shutdown();
    }

    void UnixWindow::onUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }

    void UnixWindow::setVSync(bool enabled)
    {
        if (enabled)
        {
            glfwSwapInterval(1);
        }
        else {
            glfwSwapInterval(0);
        }

        m_Data.vSync = enabled;
    }

    bool UnixWindow::isVSync()
    {
        return m_Data.vSync;
    }

    void UnixWindow::init(const WindowProps &props)
    {
        m_Data.title = props.title;
        m_Data.width = props.width;
        m_Data.height = props.height;

        HZ_CORE_INFO("Creating window {0} ({1}, {2})", props.title, props.height, props.width);

        if (!s_GLFWInitialized)
        {
            int success = glfwInit();
            HZ_ASSERT(success, "Could not initialize GLFW");
            s_GLFWInitialized = true;
        }

        m_Window = glfwCreateWindow((int) props.width, (int) props.height, m_Data.title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_Window);
        glfwSetWindowUserPointer(m_Window, &m_Data);
        setVSync(true);

        // set GLFW callbacks
        glfwSetWindowSizeCallback(m_Window, [] (GLFWwindow *window, int width, int height)
        {
            auto data = *(WindowData*) glfwGetWindowUserPointer(window);
            data.width = width;
            data.height = height;

            WindowResizeEvent event(width, height);
            data.eventCallback(event);
        });

        glfwSetWindowCloseCallback(m_Window, [] (GLFWwindow *window)
        {
            auto data = *(WindowData*) glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.eventCallback(event);
        });

        glfwSetKeyCallback(m_Window, [] (GLFWwindow *window, int key, int scanCode, int action, int mods)
        {
            auto data = *(WindowData*) glfwGetWindowUserPointer(window);

            switch (action) {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(key, 0);
                    data.eventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
                    data.eventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key, 1);
                    data.eventCallback(event);
                    break;
                }
            }
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow *window, int button, int action, int modes)
        {
            auto data = *(WindowData*) glfwGetWindowUserPointer(window);

            switch (action) {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button);
                    data.eventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(button);
                    data.eventCallback(event);
                    break;
                }
            }
        });
    }

    void UnixWindow::shutdown()
    {
        glfwDestroyWindow(m_Window);
    }

}
