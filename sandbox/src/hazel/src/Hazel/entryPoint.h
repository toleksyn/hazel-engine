#pragma once

#include "application.h"
#include "hazel.h"

extern Hazel::Application* Hazel::createApplication();

int main (int argc, char** argv)
{
    Hazel::Log::init();

    auto app = Hazel::createApplication();
    app->run();
    delete app;
}
