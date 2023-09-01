#pragma once

#include "application.h"
#include "hazel.h"

extern Hazel::Application* Hazel::createApplication();

int main (int argc, char** argv) {
    Hazel::Log::init();
    HZ_CORE_WARN("Initialized log!");
    HZ_INFO("Hello var {0}", 6);

    auto app = Hazel::createApplication();
    app->run();
    delete app;
}
