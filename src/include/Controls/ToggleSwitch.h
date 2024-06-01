#pragma once
#include <Controls/ControlToolTippable.h>
#include <string>

namespace RanGui
{
    class ToggleSwitch : public ControlToolTippable
    {
    public:
        ToggleSwitch(float pos_x, float pos_y, float width, float height);

    public:
        virtual void Render(Graphics &graphics) override;
        virtual void Initialize(Graphics &graphics) override;

    public:
        void SetIsChecked(bool on);
        bool IsChecked() const;

    public:
        void SetBackgroundColor(const RAN_GUI_COLOR_F &color);
        void SetBorderColor(const RAN_GUI_COLOR_F &color);
        void SetThumbColor(const RAN_GUI_COLOR_F &color);

    public:
        void OnMouseDown(float x, float y) override;

    private:
        bool m_isOn;
        RAN_GUI_COLOR_F m_backgroundColor;
        RAN_GUI_COLOR_F m_borderColor;
        RAN_GUI_COLOR_F m_thumbColor;

        Microsoft::WRL::ComPtr<RAN_GUI_SOLID_COLOR_BRUSH> m_pBackgroundBrush;
        Microsoft::WRL::ComPtr<RAN_GUI_SOLID_COLOR_BRUSH> m_pBorderBrush;
        Microsoft::WRL::ComPtr<RAN_GUI_SOLID_COLOR_BRUSH> m_pThumbBrush;
    };
}