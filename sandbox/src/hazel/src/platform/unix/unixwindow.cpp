#include "unixwindow.h"
#include "../../Hazel/log.h"
#include "../../Hazel/events/applicationEvent.h"
#include "../../Hazel/events/mouseEvent.h"
#include "../../Hazel/events/keyEvent.h"
#include "glad/glad.h"

namespace Hazel {

    static bool s_GLFWInitialized = false;

    static void glfwErrorCallback(int error, const char* description) {
        HZ_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
    }

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

        HZ_CORE_INFO("Creating Unix window {0} ({1}, {2})", props.title, props.height, props.width);

        if (!s_GLFWInitialized)
        {
            int success = glfwInit();
            HZ_ASSERT(success, "Could not initialize GLFW");
            glfwSetErrorCallback(glfwErrorCallback);
            s_GLFWInitialized = true;
        }

        m_Window = glfwCreateWindow((int) props.width, (int) props.height, m_Data.title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_Window);
        int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
        HZ_CORE_ASSERT(status, "Failed to initialize GLAD");
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

        glfwSetScrollCallback(m_Window, [](GLFWwindow *window, double xOffset, double yOffset)
        {
            auto data = *(WindowData*) glfwGetWindowUserPointer(window);
            MouseScrolledEvent event((float) xOffset, (float) yOffset);
            data.eventCallback(event);
        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow *window, double xPos, double yPos)
        {
            auto data = *(WindowData*) glfwGetWindowUserPointer(window);
            MouseMovedEvent event((double) xPos, (double) yPos);
            data.eventCallback(event);
        });
    }

    void UnixWindow::shutdown()
    {
        glfwDestroyWindow(m_Window);
    }

}
