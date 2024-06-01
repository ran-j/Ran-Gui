#pragma once
#include <Controls/Control.h>
#include <Controls/Layout/Layout.h>
#include <vector>
#include <memory>

namespace RanGui
{
    class Panel : public Control
    {
    public:
        Panel(float pos_x, float pos_y, float width, float height);

    public:
        virtual void Render(Graphics &graphics) override;
        virtual void Initialize(Graphics &graphics) override;

    public:
        void SetBackgroundColor(const RAN_GUI_COLOR_F &color);
        void SetBorderColor(const RAN_GUI_COLOR_F &color);

    public:
        void AddControl(std::unique_ptr<Control> control, const bool &keepRelativePosition = false);

    public:
        void SetLayout(std::unique_ptr<Layout> layout);
        void AddControlToLayout(std::unique_ptr<Control> control);

    public:
        void EnableWindowMove(bool enable);

    public:
        virtual void OnMouseMove(float x, float y) override;
        virtual void OnMouseDown(float x, float y) override;
        virtual void OnMouseUp(float x, float y) override;
        virtual void OnMouseWheel(float delta) override;
        virtual void OnKeyDown(WPARAM key) override;
        virtual void OnChar(WPARAM ch) override;

    public:
        virtual void SetPosition(float x, float y) override;

    protected:
        bool m_moveEnabled;
        bool m_dragging;
        float m_dragStartX;
        float m_dragStartY;

        Control *m_focusedControl;
        RAN_GUI_COLOR_F m_backgroundColor;
        RAN_GUI_COLOR_F m_borderColor;
        std::unique_ptr<Layout> m_layout;
        std::vector<std::unique_ptr<Control>> m_controls;
        Microsoft::WRL::ComPtr<RAN_GUI_SOLID_COLOR_BRUSH> m_pBrush;
        Microsoft::WRL::ComPtr<RAN_GUI_SOLID_COLOR_BRUSH> m_pBorderBrush;
    };
}