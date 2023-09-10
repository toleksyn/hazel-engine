#pragma once

#include "Hazel/hazel.h"

extern Hazel::Application* Hazel::CreateApplication();

int main (int argc, char** argv)
{
    Hazel::Log::Init();
    
    auto app = Hazel::CreateApplication();
    app->Run();
    delete app;
}
