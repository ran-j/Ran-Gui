#include <Controls/Panel.h>
#include <Render/Graphics.h>
#include <Controls/ControlUtils.h>

namespace RanGui
{
    Panel::Panel(float pos_x, float pos_y, float width, float height)
        : Control(pos_x, pos_y, width, height), m_moveEnabled(false), m_dragging(false), m_backgroundColor(ControlColor::White), m_borderColor(ControlColor::Black)
    {
    }

    void Panel::Initialize(Graphics &graphics)
    {
        if (!graphics.IsValid())
            return;

        Control::Initialize(graphics);

        auto renderTarget = graphics.GetRenderTarget();
        renderTarget->CreateSolidColorBrush(m_backgroundColor, &m_pBrush);
        renderTarget->CreateSolidColorBrush(m_borderColor, &m_pBorderBrush);

        for (auto &control : m_controls)
        {
            control->Initialize(graphics);
        }

        if (m_layout)
        {
            m_layout->Initialize(graphics);
            m_layout->SetRelativePosition(m_x, m_y);
            m_layout->Arrange();
        }
    }

    void Panel::Render(Graphics &graphics)
    {
        if (!m_isVisible)
            return;

        graphics.FillRectangle(RAN_GUI_RECT(m_x, m_y, m_x + m_width, m_y + m_height), m_pBrush.Get());
        graphics.DrawRectangleRect(RAN_GUI_RECT(m_x, m_y, m_x + m_width, m_y + m_height), m_pBorderBrush.Get(), 1.0f);

        for (auto &control : m_controls)
        {
            control->Render(graphics);
        }

        if (m_layout)
        {
            m_layout->Render(graphics);
        }
    }

    void Panel::AddControl(std::unique_ptr<Control> control, const bool &keepRelativePosition)
    {
        if (!keepRelativePosition)
        {
            control->SetRelativePosition(m_x, m_y);
        }
        m_controls.push_back(std::move(control));
    }

    void Panel::AddControlToLayout(std::unique_ptr<Control> control)
    {
        if (m_layout)
        {
            m_layout->AddControl(std::move(control));
            m_layout->Arrange();
        }
    }

    void Panel::EnableWindowMove(bool enable)
    {
        m_moveEnabled = enable;
    }

    void Panel::SetLayout(std::unique_ptr<Layout> layout)
    {
        m_layout = std::move(layout);
        // m_layout->SetPosition(m_x, m_y);
        m_layout->Arrange();
    }

    void Panel::SetBackgroundColor(const RAN_GUI_COLOR_F &color)
    {
        m_backgroundColor = color;
        Initialize(*m_graphics);
    }

    void Panel::SetBorderColor(const RAN_GUI_COLOR_F &color)
    {
        m_borderColor = color;
        Initialize(*m_graphics);
    }

    void Panel::OnMouseMove(float x, float y)
    {
        if (m_dragging && m_moveEnabled)
        {
            float dx = x - m_dragStartX;
            float dy = y - m_dragStartY;
            SetPosition(m_x + dx, m_y + dy);
            m_dragStartX = x;
            m_dragStartY = y;
        }

        if (m_layout)
        {
            m_layout->OnMouseMove(x, y);
        }
        for (auto &control : m_controls)
        {
            control->OnMouseMove(x, y);
        }
    }

    void Panel::OnMouseDown(float x, float y)
    {
        if (Intersect(x, y) && m_moveEnabled)
        {
            m_dragging = true;
            m_dragStartX = x;
            m_dragStartY = y;
        }

        if (m_layout)
        {
            m_layout->OnMouseDown(x, y);
        }
        ControlUtils::HandleMouseDown(m_controls, m_focusedControl, x, y);
    }

    void Panel::OnMouseUp(float x, float y)
    {
        m_dragging = false;

        if (m_layout)
        {
            m_layout->OnMouseUp(x, y);
        }
        for (auto &control : m_controls)
        {
            control->OnMouseUp(x, y);
        }
    }

    void Panel::OnKeyDown(WPARAM key)
    {
        if (m_layout)
        {
            m_layout->OnKeyDown(key);
        }
        for (auto &control : m_controls)
        {
            control->OnKeyDown(key);
        }
    }

    void Panel::OnMouseWheel(float delta)
    {
        if (m_layout)
        {
            m_layout->OnMouseWheel(delta);
        }
        for (auto &control : m_controls)
        {
            control->OnMouseWheel(delta);
        }
    }

    void Panel::OnChar(WPARAM ch)
    {
        if (m_layout)
        {
            m_layout->OnChar(ch);
        }
        for (auto &control : m_controls)
        {
            control->OnChar(ch);
        }
    }

    void Panel::SetPosition(float x, float y)
    {
        Control::SetPosition(x, y);

        if (m_layout)
        {
            // TODO maybe we shouldn't set the position of the layout here
            m_layout->SetRelativePosition(x, y);
            m_layout->Arrange();
        }
    }
}
