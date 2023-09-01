#include "application.h"
#include "events/applicationEvent.h"
#include "log.h"

namespace Hazel {
    Application::Application()
    {

    }

    Application::~Application()
    {

    }

    void Application::run()
    {
        WindowResizeEvent e(1200, 720);
        HZ_TRACE(e);
    }
}
