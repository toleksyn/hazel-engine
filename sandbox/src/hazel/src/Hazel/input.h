#pragma once
#include "core.h"

namespace Hazel {
    class HAZEL_API Input
    {
    public:
        inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
        inline static bool IsMouseButtonPressed(int button)
        {
            return s_Instance->IsMouseButtonPressedImpl(button);
        }

        inline static std::pair<double, double> GetMousePosition()
        {
            return s_Instance->GetMousePositionImpl();
        }
        inline static bool GetMouseX() { return s_Instance->GetMouseXImpl(); }
        inline static bool GetMouseY() { return s_Instance->GetMouseYImpl(); }

    protected:
        virtual bool IsKeyPressedImpl(int keycode) = 0;
        virtual bool IsMouseButtonPressedImpl(int button) = 0;
        virtual std::pair<double, double> GetMousePositionImpl() = 0;
        virtual bool GetMouseXImpl() = 0;
        virtual bool GetMouseYImpl() = 0;
    private:
        static Input* s_Instance;
    };
}
