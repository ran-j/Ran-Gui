#include <Controls/Layout/Layout.h>
#include <Render/Graphics.h>
#include <Controls/ControlUtils.h>

namespace RanGui
{
    Layout::Layout(float x, float y, float width, float height, float spacing)
        : Control(x, y, width, height), m_spacing(spacing)
    {
    }

    void Layout::AddControl(std::unique_ptr<Control> control)
    {
        m_controls.push_back(std::move(control));
    }

    Control *Layout::GetLastControl() const
    {
        return m_controls.back().get();
    }

    void Layout::Initialize(Graphics &graphics)
    {
        Renderable::Initialize(graphics);
        for (auto &control : m_controls)
        {
            control->Initialize(graphics);
        }
    }

    void Layout::Render(Graphics &graphics)
    {
        for (auto &control : m_controls)
        {
            if (control->IsVisible())
            {
                control->Render(graphics);
            }
        }
    }

    void Layout::OnMouseMove(float x, float y)
    {
        for (auto &control : m_controls)
        {
            control->OnMouseMove(x, y);
        }
    }

    void Layout::OnMouseDown(float x, float y)
    {
        ControlUtils::HandleMouseDown(m_controls, m_focusedControl, x, y);
    }

    void Layout::OnMouseUp(float x, float y)
    {
        for (auto &control : m_controls)
        {
            control->OnMouseUp(x, y);
        }
    }

    void Layout::OnKeyDown(WPARAM key)
    {
        for (auto &control : m_controls)
        {
            control->OnKeyDown(key);
        }
    }

    void Layout::OnMouseWheel(float delta)
    {
        for (auto &control : m_controls)
        {
            control->OnMouseWheel(delta);
        }
    }

    void Layout::OnChar(WPARAM ch)
    {
        for (auto &control : m_controls)
        {
            control->OnChar(ch);
        }
    }
}