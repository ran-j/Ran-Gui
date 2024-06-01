#include <Controls/Control.h>
#include <Events/MouseEvent.h>

namespace RanGui
{
    void Control::OnMouseMove(float x, float y)
    {
        auto event = MouseEvent(EventType::MouseMove, x, y);
        DispatchEvent(event);
        bool wasHover = m_isHover;
        m_isHover = Intersect(x, y);
        if (m_isHover && !wasHover)
        {
            event = MouseEvent(EventType::MouseEnter, x, y);
            DispatchEvent(event);
        }
        else if (!m_isHover && wasHover)
        {
            event = MouseEvent(EventType::MouseLeave, x, y);
            DispatchEvent(event);
        }
    }

    void Control::OnMouseDown(float x, float y)
    {
        UNREFERENCED_PARAMETER(x);
        UNREFERENCED_PARAMETER(y);
    }

    void Control::OnMouseUp(float x, float y)
    {
        auto event = MouseEvent(EventType::MouseUp, x, y);
        DispatchEvent(event);
    }

    void Control::OnMouseWheel(float delta)
    {
        UNREFERENCED_PARAMETER(delta);
    }

    void Control::OnKeyDown(WPARAM key)
    {
        UNREFERENCED_PARAMETER(key);
    }

    void Control::OnChar(WPARAM ch)
    {
        UNREFERENCED_PARAMETER(ch);
    }

    void Control::OnFocus(bool focused)
    {
        m_isFocused = focused;
        if (!m_isFocused)
        {
            return;
        }

        auto event = MouseEvent(EventType::Click, m_x, m_y);
        DispatchEvent(event);
    }

    void Control::AddEventListener(std::shared_ptr<EventListener> listener)
    {
        m_eventListeners.push_back(listener);
    }

    void Control::RemoveEventListener(std::shared_ptr<EventListener> listener)
    {
        m_eventListeners.erase(
            std::remove(m_eventListeners.begin(), m_eventListeners.end(), listener),
            m_eventListeners.end());
    }

    bool Control::IsFocused() const
    {
        return m_isFocused;
    }

    void Control::DispatchEvent(const Event &event)
    {
        for (auto &listener : m_eventListeners)
        {
            listener->OnEvent(event);
        }
    }
}