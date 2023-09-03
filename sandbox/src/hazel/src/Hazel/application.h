#pragma once
#include "core.h"
#include "events/applicationEvent.h"
#include "window.h"

namespace Hazel {

    class HAZEL_API Application
    {
    public:
        Application();
        virtual ~Application();

        void run();
        void onEvent(Event& e);
    private:
        bool onWindowClose(WindowCloseEvent& e);
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
    };

    Application* createApplication();
}
