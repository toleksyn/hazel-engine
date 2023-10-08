#pragma once

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "Hazel/window.h"

namespace Hazel {

    class UnixWindow : public Window
    {
    public:
        UnixWindow(const WindowProps& props);
        virtual ~UnixWindow();

        void OnUpdate() override;

        inline unsigned int GetWidth() const override { return m_Data.width; }
        inline unsigned int GetHeight() const override { return m_Data.height; }

        inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.eventCallback = callback; }
        void SetVSync(bool enabled) override;
        bool IsVSync() override;
        inline void* GetNativeWindow() const override { return m_Window; }

    private:
        virtual void Init(const WindowProps& props);
        virtual void Shutdown();

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
