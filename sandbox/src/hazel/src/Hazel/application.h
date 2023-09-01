#pragma once

namespace Hazel {
    class Application
    {
    public:
        Application();
        virtual ~Application();

        void run();
    };

    Application* createApplication();
}
