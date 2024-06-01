
#pragma once

#include <vector>
#include <memory>
#include <Render/Graphics.h>
#include <Controls/Control.h>

namespace RanGui
{
    class ControlManager
    {
    public:
        ControlManager(Graphics *graphics);
        ~ControlManager();

    public:
        void AddControl(std::unique_ptr<Control> control);
        void RemoveControl(Control *control);

    public:
        void Render(Graphics &graphics);

    public:
        void OnMouseMove(float x, float y);
        void OnMouseDown(float x, float y);
        void OnMouseUp(float x, float y);
        void OnMouseWheel(float delta);
        void OnKeyDown(WPARAM key);
        void OnChar(WPARAM ch);

    private:
        Graphics *m_graphics;
        std::vector<std::unique_ptr<Control>> m_controls;
        Control *m_focusedControl = nullptr;
    };
}