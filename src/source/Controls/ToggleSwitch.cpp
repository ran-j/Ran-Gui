#include <Controls/ToggleSwitch.h>
#include <Render/Graphics.h>

namespace RanGui
{
    ToggleSwitch::ToggleSwitch(float pos_x, float pos_y, float width, float height)
        : ControlToolTippable(pos_x, pos_y, width, height),
          m_isOn(false),
          m_backgroundColor(ControlColor::LightGray),
          m_borderColor(ControlColor::Black),
          m_thumbColor(ControlColor::White)
    {
    }

    void ToggleSwitch::Initialize(Graphics &graphics)
    {
        ControlToolTippable::Initialize(graphics);

        if (!graphics.IsValid())
            return;

        auto renderTarget = graphics.GetRenderTarget();

        renderTarget->CreateSolidColorBrush(m_backgroundColor, &m_pBackgroundBrush);
        renderTarget->CreateSolidColorBrush(m_borderColor, &m_pBorderBrush);
        renderTarget->CreateSolidColorBrush(m_thumbColor, &m_pThumbBrush);
    }

    void ToggleSwitch::Render(Graphics &graphics)
    {
        ControlToolTippable::Render(graphics);
        
        if (!m_isVisible)
            return;

        auto background = RAN_GUI_ROUNDED_RECT(RAN_GUI_RECT(m_x, m_y, m_x + m_width, m_y + m_height), m_height / 2, m_height / 2);
        graphics.FillRoundedRectangle(background, m_pBackgroundBrush.Get());
        graphics.DrawRoundedRectangle(background, m_pBorderBrush.Get(), 1.0f);

        // Draw the thumb
        float thumbWidth = m_height;
        float thumbX = m_isOn ? (m_x + m_width - thumbWidth) : m_x;
        graphics.FillEllipse(RAN_GUI_ELLIPSE(RAN_GUI_POINT(thumbX + thumbWidth / 2, m_y + m_height / 2), thumbWidth / 2, thumbWidth / 2), m_pThumbBrush.Get());
    }

    void ToggleSwitch::SetIsChecked(bool on)
    {
        m_isOn = on;
    }

    bool ToggleSwitch::IsChecked() const
    {
        return m_isOn;
    }

    void ToggleSwitch::SetBackgroundColor(const RAN_GUI_COLOR_F &color)
    {
        m_backgroundColor = color;
        Initialize(*m_graphics);
    }

    void ToggleSwitch::SetBorderColor(const RAN_GUI_COLOR_F &color)
    {
        m_borderColor = color;
        Initialize(*m_graphics);
    }

    void ToggleSwitch::SetThumbColor(const RAN_GUI_COLOR_F &color)
    {
        m_thumbColor = color;
        Initialize(*m_graphics);
    }

    void ToggleSwitch::OnMouseDown(float x, float y)
    {
        if (Intersect(x, y))
        {
            m_isOn = !m_isOn;
        }
    }
}