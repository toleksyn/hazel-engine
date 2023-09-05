#include <src/hazel.h>

class ExampleLayer : public Hazel::Layer
{
public:
    ExampleLayer()
        : Layer("Example")
    {
    }

    void onUpdate() override
    {
        HZ_INFO("ExampleLayer::Update");
    }

    void onEvent(Hazel::Event& e) override
    {
        HZ_TRACE("{0}", e);
    }
};

class Sandbox : public Hazel::Application
{
public:
    Sandbox()
    {
        pushLayer(new ExampleLayer());
    }

    ~Sandbox()
    {

    }
};

Hazel::Application* Hazel::createApplication()
{
    return new Sandbox();
}
