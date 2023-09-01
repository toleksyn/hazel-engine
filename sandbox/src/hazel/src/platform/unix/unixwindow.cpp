#include "unixwindow.h"
#include "../../Hazel/log.h"

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
    }

    void UnixWindow::shutdown()
    {
        glfwDestroyWindow(m_Window);
    }

}
