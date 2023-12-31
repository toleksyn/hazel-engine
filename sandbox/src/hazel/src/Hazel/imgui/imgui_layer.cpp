#include "Hazel/key_codes.h"
#include "hzpch.h"
#include "Hazel/log.h"
#include "Hazel/application.h"
#include "Hazel/events/mouse_event.h"
#include "Hazel/events/key_event.h"
#include "imgui_layer.h"
#include "platform/opengl/imgui_impl_opengl_renderer.h"

// TEMPORARY
#include "GLFW/glfw3.h"


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
        ImGui::StyleColorsDark();

        ImGuiIO &io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

#ifdef __APPLE__
        io.DisplayFramebufferScale = ImVec2(2.0f, 2.0f);
#endif

        io.KeyMap[ImGuiKey_Tab] = HZ_KEY_TAB;
        io.KeyMap[ImGuiKey_LeftArrow] = HZ_KEY_LEFT;
        io.KeyMap[ImGuiKey_RightArrow] = HZ_KEY_RIGHT;
        io.KeyMap[ImGuiKey_UpArrow] = HZ_KEY_UP;
        io.KeyMap[ImGuiKey_DownArrow] = HZ_KEY_DOWN;
        io.KeyMap[ImGuiKey_PageUp] = HZ_KEY_PAGE_UP;
        io.KeyMap[ImGuiKey_PageDown] = HZ_KEY_PAGE_DOWN;
        io.KeyMap[ImGuiKey_Home] = HZ_KEY_HOME;
        io.KeyMap[ImGuiKey_End] = HZ_KEY_END;
        io.KeyMap[ImGuiKey_Insert] = HZ_KEY_INSERT;
        io.KeyMap[ImGuiKey_Delete] = HZ_KEY_DELETE;
        io.KeyMap[ImGuiKey_Backspace] = HZ_KEY_BACKSPACE;
        io.KeyMap[ImGuiKey_Space] = HZ_KEY_SPACE;
        io.KeyMap[ImGuiKey_Enter] = HZ_KEY_ENTER;
        io.KeyMap[ImGuiKey_Escape] = HZ_KEY_ESCAPE;
        io.KeyMap[ImGuiKey_A] = HZ_KEY_A;
        io.KeyMap[ImGuiKey_C] = HZ_KEY_C;
        io.KeyMap[ImGuiKey_V] = HZ_KEY_V;
        io.KeyMap[ImGuiKey_X] = HZ_KEY_X;
        io.KeyMap[ImGuiKey_Y] = HZ_KEY_Y;
        io.KeyMap[ImGuiKey_Z] = HZ_KEY_Z;

        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void ImGuiLayer::OnDetach()
    {

    }

    void ImGuiLayer::OnUpdate()
    {
        ImGuiIO &io = ImGui::GetIO();
        Application &app = Application::Get();
        io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

        float time = (float) glfwGetTime();
        io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
        m_Time = time;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        bool static show = true;
        ImGui::ShowDemoWindow(&show);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiLayer::OnEvent(Event &e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseButtonPressedEvent>(
            HZ_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
        dispatcher.Dispatch<MouseButtonReleasedEvent>(
            HZ_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
        dispatcher.Dispatch<MouseMovedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
        dispatcher.Dispatch<MouseScrolledEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
        dispatcher.Dispatch<KeyPressedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
        dispatcher.Dispatch<KeyTypedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
        dispatcher.Dispatch<KeyReleasedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
        dispatcher.Dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
    }

    bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent &e)
    {
        ImGuiIO &io = ImGui::GetIO();
        io.MouseDown[e.GetMouseButton()] = true;
        return false;
    }

    bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent &e)
    {
        ImGuiIO &io = ImGui::GetIO();
        io.MouseDown[e.GetMouseButton()] = false;
        return false;
    }

    bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent &e)
    {
        ImGuiIO &io = ImGui::GetIO();
        io.MousePos = ImVec2(e.GetX(), e.GetY());
        return false;
    }

    bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent &e)
    {
        ImGuiIO &io = ImGui::GetIO();
        io.MouseWheelH += e.GetXOffset();
        io.MouseWheel += e.GetYOffset();
        return false;
    }

    bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent &e)
    {
        ImGuiIO &io = ImGui::GetIO();
        io.KeysDown[e.GetKeyCode()] = true;

        io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
        io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
        io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
        io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
        return false;
    }

    bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent &e)
    {
        ImGuiIO &io = ImGui::GetIO();
        io.KeysDown[e.GetKeyCode()] = false;
        return false;
    }

    bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent &e)
    {
        ImGuiIO &io = ImGui::GetIO();
        int keycode = e.GetKeyCode();

        if (keycode > 0 && keycode < 0x10000)
        {
            io.AddInputCharacter((unsigned short) keycode);
        }
        return false;
    }

    bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent &e)
    {
        ImGuiIO &io = ImGui::GetIO();
        io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
#ifdef __APPLE__
        io.DisplayFramebufferScale = ImVec2(2.0f, 2.0f);
#else
        io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
#endif
        glViewport(0, 0, e.GetWidth(), e.GetHeight());
        return false;
    }
}
