#include <Controls/Slider.h>
#include <Render/Graphics.h>

namespace RanGui
{
    Slider::Slider(float pos_x, float pos_y, float width, float height)
        : Control(pos_x, pos_y, width, height), m_value(0.5f),
          m_trackColor(ControlColor::LightGray),
          m_thumbColor(ControlColor::DarkGray)
    {
    }

    void Slider::Initialize(Graphics &graphics)
    {
        if (!graphics.IsValid())
            return;

        Renderable::Initialize(graphics);

        auto renderTarget = graphics.GetRenderTarget();

        renderTarget->CreateSolidColorBrush(m_trackColor, &m_pTrackBrush);
        renderTarget->CreateSolidColorBrush(m_thumbColor, &m_pThumbBrush);
    }

    void Slider::Render(Graphics &graphics)
    {
        if (!m_isVisible)
            return;

        DrawTrack(graphics);
        if (m_style == SliderStyle::Circular)
        {
            DrawCircularThumb(graphics);
        }
        else
        {
            DrawThumb(graphics);
        }
    }

    void Slider::DrawTrack(Graphics &graphics)
    {
        graphics.FillRectangle(RAN_GUI_RECT(m_x, m_y + m_height / 2 - 2, m_x + m_width, m_y + m_height / 2 + 2), m_pTrackBrush.Get());
    }

    void Slider::DrawThumb(Graphics &graphics)
    {
        float thumbX = m_x + m_value * m_width;
        graphics.FillEllipse(RAN_GUI_ELLIPSE(RAN_GUI_POINT(thumbX, m_y + m_height / 2), m_height / 2, m_height / 2), m_pThumbBrush.Get());
    }

    void Slider::DrawCircularThumb(Graphics &graphics)
    {
        float thumbX = m_x + m_value * m_width;
        float radius = m_height / 2;
        auto ellipse = RAN_GUI_ELLIPSE(RAN_GUI_POINT(thumbX, m_y + m_height / 2), radius, radius);

        // Draw outer circle
        graphics.FillEllipse(ellipse, m_pThumbBrush.Get());
        graphics.DrawEllipse(ellipse, m_pTrackBrush.Get(), 2.0f);

        // Draw inner circle
        float innerRadius = radius - 4;
        auto innerEllipse = RAN_GUI_ELLIPSE(RAN_GUI_POINT(thumbX, m_y + m_height / 2), innerRadius, innerRadius);
        graphics.FillEllipse(innerEllipse, m_pTrackBrush.Get());
    }

    void Slider::SetValue(float value)
    {
        if (!m_isDragging)
            return;

        m_value = min(max(value, 0.0f), 1.0f);
    }

    float Slider::GetValue() const
    {
        return m_value;
    }

    void Slider::SetTrackColor(const RAN_GUI_COLOR_F &color)
    {
        m_trackColor = color;
        Initialize(*m_graphics);
    }

    void Slider::SetThumbColor(const RAN_GUI_COLOR_F &color)
    {
        m_thumbColor = color;
        Initialize(*m_graphics);
    }

    void Slider::OnMouseMove(float x, float y)
    {
        if (Intersect(x, y))
        {
            SetValue((x - m_x) / m_width);
        }
    }

    void Slider::OnMouseDown(float x, float y)
    {
        if (Intersect(x, y))
        {
            m_isDragging = true;
            SetValue((x - m_x) / m_width);
        }
        else
        {
            m_isDragging = false;
        }
    }

    void Slider::OnMouseUp(float x, float y)
    {
        UNREFERENCED_PARAMETER(x);
        UNREFERENCED_PARAMETER(y);
        m_isDragging = false;
    }
}