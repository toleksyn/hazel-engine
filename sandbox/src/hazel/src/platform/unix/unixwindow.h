#pragma once

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include "../../Hazel/window.h"

namespace Hazel {

    class UnixWindow : public Window
    {
    public:
        UnixWindow(const WindowProps& props);
        virtual ~UnixWindow();

        void onUpdate() override;

        inline unsigned int getWidth() const override { return m_Data.width; }
        inline unsigned int getHeight() const override { return m_Data.height; }

        inline void setEventCallback(const EventCallbackFn& callback) override { m_Data.eventCallback = callback; }
        void setVSync(bool enabled) override;
        bool isVSync() override;

    private:
        virtual void init(const WindowProps& props);
        virtual void shutdown();

    private:
        GLFWwindow* m_Window;

        struct WindowData
        {
            std::string title;
            unsigned int width, height;
            bool vSync;

            EventCallbackFn eventCallback;
        };

        WindowData m_Data;
    };

}
