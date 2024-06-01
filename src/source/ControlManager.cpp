
#include <ControlManager.h>
#include <Controls/ControlUtils.h>

namespace RanGui
{
    ControlManager::ControlManager(Graphics *graphics)
    {
        m_graphics = graphics;
    }

    ControlManager::~ControlManager()
    {
        m_controls.clear();
    }

    void ControlManager::AddControl(std::unique_ptr<Control> control)
    {
        control->Initialize(*m_graphics);
        m_controls.push_back(std::move(control));
    }

    void ControlManager::RemoveControl(Control *control)
    {
        m_controls.erase(std::remove_if(m_controls.begin(), m_controls.end(),
                                        [&](const std::unique_ptr<Control> &w)
                                        { return w.get() == control; }),
                         m_controls.end());
    }

    void ControlManager::Render(Graphics &graphics)
    {
        for (const auto &control : m_controls)
        {
            if (control->IsVisible())
            {
                control->Render(graphics);
            }
        }
    }

    void ControlManager::OnMouseMove(float x, float y)
    {
        for (auto &control : m_controls)
        {
            control->OnMouseMove(x, y);
        }
    }

    void ControlManager::OnMouseDown(float x, float y)
    {
        ControlUtils::HandleMouseDown(m_controls, m_focusedControl, x, y);
    }

    void ControlManager::OnMouseUp(float x, float y)
    {
        for (auto &control : m_controls)
        {
            control->OnMouseUp(x, y);
        }
    }

    void ControlManager::OnKeyDown(WPARAM key)
    {
        if (m_focusedControl)
        {
            m_focusedControl->OnKeyDown(key);
        }
    }

    void ControlManager::OnMouseWheel(float delta)
    {
        for (auto &control : m_controls)
        {
            control->OnMouseWheel(delta);
        }
    }

    void ControlManager::OnChar(WPARAM ch)
    {
        if (m_focusedControl)
        {
            m_focusedControl->OnChar(ch);
        }
    }
}