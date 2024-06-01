#pragma once
#include <Controls/Control.h>

namespace RanGui
{
    enum class SliderStyle
    {
        Linear,
        Circular,
    };

    class Slider : public Control
    {
    public:
        Slider(float pos_x, float pos_y, float width, float height);

    public:
        virtual void Render(Graphics &graphics) override;
        virtual void Initialize(Graphics &graphics) override;

    public:
        void SetValue(float value);
        float GetValue() const;

    public:
        void SetTrackColor(const RAN_GUI_COLOR_F &color);
        void SetThumbColor(const RAN_GUI_COLOR_F &color);

    public:
        void SetStyle(SliderStyle style) { m_style = style; }

    public:
        virtual void OnMouseMove(float x, float y) override;
        virtual void OnMouseDown(float x, float y) override;
        virtual void OnMouseUp(float x, float y) override;

    private:
        float m_value;
        bool m_isDragging = false;
        SliderStyle m_style = SliderStyle::Circular;

        RAN_GUI_COLOR_F m_trackColor;
        RAN_GUI_COLOR_F m_thumbColor;

        Microsoft::WRL::ComPtr<RAN_GUI_SOLID_COLOR_BRUSH> m_pTrackBrush;
        Microsoft::WRL::ComPtr<RAN_GUI_SOLID_COLOR_BRUSH> m_pThumbBrush;

        void DrawTrack(Graphics &graphics);
        void DrawThumb(Graphics &graphics);
        void DrawCircularThumb(Graphics &graphics);
    };
}