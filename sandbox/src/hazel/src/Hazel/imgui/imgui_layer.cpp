#include "hzpch.h"
#include "imgui_layer.h"

#include "platform/opengl/imgui_impl_opengl_renderer.h"

namespace Hazel {

    ImGuiLayer::ImGuiLayer()
        : Layer("ImGui layer")
    {

    }

    ImGuiLayer::~ImGuiLayer()
    {

    }

    void ImGuiLayer::OnAttach()
    {
        ImGui::CreateContext();
    }

    void ImGuiLayer::OnDetach()
    {

    }

    void ImGuiLayer::OnUpdate()
    {

    }

    void ImGuiLayer::OnEvent(Event &e)
    {

    }

}
