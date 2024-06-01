#include <Controls/ControlToolTippable.h>

namespace RanGui
{
    ControlToolTippable::ControlToolTippable(float pos_x, float pos_y, float width, float height) : Control(pos_x, pos_y, width, height)
    {
    }

    void ControlToolTippable::SetupTooltip(const std::wstring &text, float pos_x, float pos_y, float width, float height, const RAN_GUI_COLOR_F &background, const RAN_GUI_COLOR_F &textColor)
    {
        if (!m_tooltip)
        {
            m_tooltip = std::make_unique<Tooltip>(m_x + pos_x, m_y + pos_y, width, height);
            m_tooltip->SetBackgroundColor(background);
            m_tooltip->SetTextColor(textColor);
            Initialize(*m_graphics);
        }
        else
        {
            m_tooltip->SetPosition(m_x + pos_x, m_y + pos_y);
            m_tooltip->SetBackgroundColor(background);
            m_tooltip->SetTextColor(textColor);
            m_tooltip->SetSize(width, height);
        }

        m_tooltip->SetText(text);
    }

    void ControlToolTippable::SetTooltipTextColor(const RAN_GUI_COLOR_F &color)
    {
        if (!m_tooltip)
        {
            m_tooltip = std::make_unique<Tooltip>(m_x, m_y, 100.f, 20.f);
            Initialize(*m_graphics);
        }

        m_tooltip->SetTextColor(color);
    }

    void ControlToolTippable::SetTooltipBackgroundColor(const RAN_GUI_COLOR_F &color)
    {
        if (!m_tooltip)
        {
            m_tooltip = std::make_unique<Tooltip>(m_x, m_y, 100.f, 20.f);
            Initialize(*m_graphics);
        }

        m_tooltip->SetBackgroundColor(color);
    }

    void ControlToolTippable::Initialize(Graphics &graphics)
    {
        Control::Initialize(graphics);
        if (m_tooltip)
        {
            m_tooltip->Initialize(graphics);
        }
    }

    void ControlToolTippable::SetPosition(float x, float y)
    {
        Control::SetPosition(x, y);
        if (m_tooltip)
        {
            m_tooltip->SetPosition(m_width + x, m_height + y);
        }
    }

    void ControlToolTippable::Render(Graphics &graphics)
    {
        if (!m_isVisible)
            return;

        if (m_tooltip && m_isHover)
        {
            m_tooltip->Render(graphics);
        }
    }
}