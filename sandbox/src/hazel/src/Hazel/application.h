#pragma once
#include "core.h"
#include "window.h"

namespace Hazel {
    class HAZEL_API Application
    {
    public:
        Application();
        virtual ~Application();

        void run();
    private:
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
    };

    Application* createApplication();
}
