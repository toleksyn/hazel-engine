#pragma once
#include "Hazel/input.h"

namespace Hazel {
    class UnixInput : public Input
    {
    protected:
        virtual bool IsKeyPressedImpl(int keycode) override;
        virtual bool IsMouseButtonPressedImpl(int button) override;
        virtual std::pair<double, double> GetMousePositionImpl() override;
        virtual bool GetMouseXImpl() override;
        virtual bool GetMouseYImpl() override;
    };
}


