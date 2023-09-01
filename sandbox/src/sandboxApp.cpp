#include <src/hazel.h>

class Sandbox : public Hazel::Application
{
public:
    Sandbox()
    {

    }

    ~Sandbox()
    {

    }
};

Hazel::Application* Hazel::createApplication()
{
    return new Sandbox();
}
