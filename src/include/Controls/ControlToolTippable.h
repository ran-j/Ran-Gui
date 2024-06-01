#pragma once

#include <Controls/Control.h>
#include <Controls/Tooltip.h>

namespace RanGui
{
    class ControlToolTippable : public Control
    {
    protected:
        std::unique_ptr<Tooltip> m_tooltip;

    public:
        ControlToolTippable(float pos_x, float pos_y, float width, float height);

    public:
        virtual void SetupTooltip(
            const std::wstring &text,
            float pos_x = 0.f,
            float pos_y = 0.f,
            float width = 100.f,
            float height = 20.f,
            const RAN_GUI_COLOR_F &background = {0.1f, 0.1f, 0.1f, 1.f},
            const RAN_GUI_COLOR_F &textColor = {1.f, 1.f, 1.f, 1.f});
            
        void SetTooltipTextColor(const RAN_GUI_COLOR_F &color);
        void SetTooltipBackgroundColor(const RAN_GUI_COLOR_F &color);

    public:
        virtual void SetPosition(float x, float y) override;

    public:
        virtual void Initialize(Graphics &graphics) override;
        virtual void Render(Graphics &graphics) override;
    };
}